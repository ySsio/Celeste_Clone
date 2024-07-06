#include "pch.h"
#include "CState_Dead.h"
#include "CPlayer.h"
#include "CDeadEffect.h"

#include "CTimeMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CCamera.h"

CState_Dead::CState_Dead()
	: m_AccTime(0.f)
	, m_AnimDuration(0.5f)
	, m_RespawnDuration(1.5f)
	, m_SpreadDuration(0.2f)
	, m_GatherWaitTime(1.f)
	, m_DeadEffect(nullptr)
	, m_SpreadEffect(false)
	, m_Respawn(false)
	, m_GatherEffect(false)
{
	// ī�޶� Respawn ȿ���� ȭ�� ��ü�� ������ ������ 
	// Camera�� Duration�� 1/2��ŭ �ð��� ���� �����̱� ������
	// �� �� �÷��̾ ������ �������� �Ű���� ��. 
	// ���� RespawnDuration�� DeadDuration����
	// CameraEffect�� Duration / 2��ŭ (������ 1��) Ŀ�� ��.
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
	// �ִϸ��̼� ���
	PlayAnimation();

	// ���� �ʱ�ȭ
	m_AccTime = 0.f;
	m_SpreadEffect = false;
	m_Respawn = false;
	m_GatherEffect = false;
	
	CPlayer* pPlayer = GetOwner();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	// ������� ����
	pRigid->SetFrictionCoef(FRICTION_DEAD);
	pRigid->SetFrictionY(true);

	// ���� ���� �� �ݵ�� �ٽ� ������� �������ƾ� �� ����
	pPlayer->SetPlayerDead(true);
	pRigid->SetGravity(false);
	
	// �浹�� �ݴ� �������� ƨ�ܳ��� (�ӵ� : 400.f)
	Vec2 vBounceDir = pPlayer->GetBounceDir();
	pRigid->SetVelocity(vBounceDir * 400.f);
}

void CState_Dead::FinalTick()
{
	CPlayer* pPlayer = GetOwner();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	m_AccTime += fDT;

	// Animation�� ��� ����� �� (m_AnimDuration) ���ۺ��� CDeadEffect�� �߰���.
	if (m_AccTime >= m_AnimDuration && !m_SpreadEffect)
	{
		m_DeadEffect = new CDeadEffect;
		m_DeadEffect->SetPos(pPlayer->GetPos());
		m_DeadEffect->SetBaseColor(pPlayer->GetColor());
		m_DeadEffect->SetSpreadDuration(m_SpreadDuration);
		m_DeadEffect->SetRotationDir(1.f);
		m_DeadEffect->Spread();

		Add_Object(m_DeadEffect, LAYER_TYPE::EFFECT);

		CCamera::Get()->SetCamEffect(CAM_EFFECT::RESPAWN);

		m_SpreadEffect = true;
	}
	
	Vec2 SpawnPoint = CLevelMgr::Get()->GetCurLevel()->GetSpawnPoint();

	// RespawnDuration�� ������ DeadEffect�� ������ �������� �̵���Ű��, ȸ�� ���� ������
	if (m_AccTime >= m_RespawnDuration && !m_Respawn)
	{
		m_DeadEffect->SetPos(SpawnPoint);
		m_DeadEffect->SetRotationDir(-1.f);
		
		m_Respawn = true;
	}

	// RespawnDuration�� ������ GatherWaitTime ���� ���ۺ��� �� �Ŀ� 
	// Gather()�� �����ؼ� SpreadDuration���� �� ������ ������
	if (m_AccTime >= m_RespawnDuration + m_GatherWaitTime && !m_GatherEffect)
	{
		m_DeadEffect->Gather();

		m_GatherEffect = true;
	}

	// DeadEffect�� �� ������ ���� ���� ����, �÷��̾ ������������ �ű�� ���¸� ������Ŵ
	// DeadEffect�� �����ϰ�, �÷��̾ Idle ���·� ��ȯ
	if (m_AccTime >= m_RespawnDuration + m_GatherWaitTime + m_SpreadDuration)
	{
		GetStateMachine()->ChangeState(L"Idle");
	}
	
}

void CState_Dead::Exit()
{
	CPlayer* pPlayer = GetOwner();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	Vec2 SpawnPoint = CLevelMgr::Get()->GetCurLevel()->GetSpawnPoint();

	pPlayer->SetPos(SpawnPoint);

	// �÷��̾� ���¸� ������� ����
	pPlayer->SetPlayerDead(false);
	pRigid->SetGravity(true);
	pRigid->SetFrictionCoef(FRICTION);
	pRigid->SetFrictionY(false);

	Delete_Object(m_DeadEffect);
}