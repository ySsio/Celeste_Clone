#include "pch.h"
#include "CState_Dead.h"
#include "CPlayer.h"
#include "CDeadEffect.h"

#include "CTimeMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CCamera.h"

#include "CSound.h"
#include "CAssetMgr.h"

#include "CGameMgr.h"

CState_Dead::CState_Dead()
	: m_AccTime(0.f)
	, m_AnimDuration(0.5f)
	, m_RespawnDuration(1.5f)
	, m_SpreadDuration(0.2f)
	, m_GatherWaitTime(1.f)
	, m_SpreadEffect(false)
	, m_LevelReset(false)
	, m_Respawn(false)
	, m_GatherEffect(false)
	, m_DeadEffect(nullptr)
{
	// 카메라 Respawn 효과가 화면 전체를 가리는 순간이 
	// Camera의 Duration의 1/2만큼 시간이 지난 시점이기 때문에
	// 그 때 플레이어를 리스폰 지점으로 옮겨줘야 함. 
	// 따라서 RespawnDuration이 DeadDuration보다
	// CameraEffect의 Duration / 2만큼 (지금은 1초) 커야 함.
}

CState_Dead::~CState_Dead()
{
}



void CState_Dead::PlayAnimation()
{
	Vec2 vDir = GetOwner()->GetBounceDir();

	GetBangAnimator()->End();

	if (vDir.x > 0.f)
	{
		GetBodyAnimator()->Play(L"Player_Dead_FlipX");
	}
	else
	{
		GetBodyAnimator()->Play(L"Player_Dead");
	}
	
}

void CState_Dead::Enter()
{
	// 게임매니저 데스 카운트 증가
	CGameMgr::Get()->AddDeathCount();

	// 카메라 진동 효과
	CCamera::Get()->SetCamEffect(CAM_EFFECT::SHAKE, (UINT_PTR)Vec2(2.f,0.f));

	// 애니메이션 재생
	PlayAnimation();

	// Sound 재생
	CSound* pSound = CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\char\\char_mad_death.wav");
	pSound->Play();

	CPlayer* pPlayer = GetOwner();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	// 변수 초기화
	m_AccTime = 0.f;
	m_SpreadEffect = false;
	m_Respawn = false;
	m_GatherEffect = false;
	m_SpawnPoint = pPlayer->GetPos();
	

	// 마찰계수 설정
	pRigid->SetFrictionCoef(FRICTION_DEAD);
	pRigid->SetFrictionY(true);

	// 상태 끝날 떄 반드시 다시 원래대로 돌려놓아야 할 세팅
	pPlayer->SetPlayerDead(true);
	pRigid->SetGravity(false);
	
	// 충돌한 반대 방향으로 튕겨나감 (속도 : 400.f)
	Vec2 vBounceDir = pPlayer->GetBounceDir();
	pRigid->SetVelocity(vBounceDir * 400.f);
}

void CState_Dead::FinalTick()
{
	CPlayer* pPlayer = GetOwner();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	m_AccTime += fDT;

	// 1초 지난 시점 (카메라 효과가 화면 다 가린 시점)에 레벨 reset
	if (m_AccTime >= 1.f && !m_LevelReset)
	{
		// 레벨 Reset
		Reset_Level();

		m_LevelReset = true;
	}

	// Animation이 모두 재생된 후 (m_AnimDuration) 빙글빙글 CDeadEffect를 추가함.
	if (m_AccTime >= m_AnimDuration && !m_SpreadEffect)
	{
		m_DeadEffect = new CDeadEffect;
		m_DeadEffect->SetPos(pPlayer->GetPos());
		m_DeadEffect->SetBaseColor(pPlayer->GetColor());
		m_DeadEffect->SetSpreadDuration(m_SpreadDuration);
		m_DeadEffect->SetRotationDir(1.f);
		m_DeadEffect->SetRoom(CLevelMgr::Get()->GetCurLevel()->GetCurRoom());
		m_DeadEffect->Spread();

		Add_Object(m_DeadEffect, LAYER_TYPE::EFFECT);

		CCamera::Get()->SetCamEffect(CAM_EFFECT::RESPAWN);

		m_SpreadEffect = true;
	}
	
	// RespawnDuration이 지나고 DeadEffect를 리스폰 지점으로 이동시키고, 회전 방향 변경함
	if (m_AccTime >= m_RespawnDuration && !m_Respawn)
	{
		CLevel* pLevel = CLevelMgr::Get()->GetCurLevel();
		vector<tRoom>& Rooms = pLevel->GetRooms();

		Vec2 vPos = pPlayer->GetPos();
		float dist = 10000.f;

		// 현재 룸의 모든 스폰포인트 중 죽은 곳에서 가장 가까운 지점에서 부활
		for (auto& point : Rooms[pLevel->GetCurRoom()].SpawnPoints)
		{
			float pointDist = (vPos - point).Length();
			if (dist > pointDist)
			{
				dist = pointDist;
				m_SpawnPoint = point;
			}
		}

		// 가장 가까운 스폰지점으로 이동
		pPlayer->SetPos(m_SpawnPoint);

		m_DeadEffect->SetPos(m_SpawnPoint);
		m_DeadEffect->SetRotationDir(-1.f);
		
		m_Respawn = true;
	}

	// RespawnDuration이 지나고 GatherWaitTime 동안 빙글빙글 돈 후에 
	// Gather()을 실행해서 SpreadDuration동안 한 점으로 모은다
	if (m_AccTime >= m_RespawnDuration + m_GatherWaitTime && !m_GatherEffect)
	{
		// Sound 재생
		CSound* pSound = CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\char\\char_mad_revive.wav");
		pSound->SetPosition(60.f);
		pSound->Play();

		m_DeadEffect->Gather();

		m_GatherEffect = true;
	}

	// DeadEffect가 한 점으로 모인 후의 시점, 플레이어를 스폰지점으로 옮기고 상태를 복구시킴
	// DeadEffect는 삭제하고, 플레이어를 Idle 상태로 전환
	if (m_AccTime >= m_RespawnDuration + m_GatherWaitTime + m_SpreadDuration)
	{
		GetStateMachine()->ChangeState(L"Idle");
	}
	
}

void CState_Dead::Exit()
{
	m_LevelReset = false;

	CPlayer* pPlayer = GetOwner();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	// 플레이어 상태를 원래대로 돌림
	pPlayer->SetPlayerDead(false);
	pRigid->SetGravity(true);
	pRigid->SetFrictionCoef(FRICTION);
	pRigid->SetFrictionY(false);

	Delete_Object(m_DeadEffect);
	m_DeadEffect = nullptr;
}