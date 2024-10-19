#include "pch.h"
#include "CState_Run.h"

#include "CAssetMgr.h"
#include "CSound.h"

CState_Run::CState_Run()
	: m_AccTime(0.f)
	, m_Duration(0.3f)
{

}

CState_Run::~CState_Run()
{
}

void CState_Run::PlayAnimation()
{
	Vec2 vDir = GetOwner()->GetDir();

	if (vDir.x == 1.f)
	{
		GetBangAnimator()->Play(L"Player_Bang_Run", true);
		GetBodyAnimator()->Play(L"Player_Run", true);
	}
	else if (vDir.x == -1.f)
	{
		GetBangAnimator()->Play(L"Player_Bang_Run_FlipX", true);
		GetBodyAnimator()->Play(L"Player_Run_FlipX", true);
	}
}

void CState_Run::Enter()
{
	PlayAnimation();

	// Sound 재생 (발소리)
	CSound* pSound = CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\char\\char_mad_foot_00_dirt_01.wav");
	pSound->Play();

	// 변수 초기화
	m_AccTime = 0.f;
}

void CState_Run::Exit()
{
}

void CState_Run::FinalTick()
{
	CPlayer* pPlayer = GetOwner();
	Vec2 vDir = GetOwner()->GetDir();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	if (pPlayer->IsDirChanged())
	{
		PlayAnimation();
	}
	
	if (KEY_PRESSED(KEY::LEFT))
	{
		//pRigid->MovePosition(pPlayer->GetPos() + Vec2(-400.f, 0.f) * fDT);
		pRigid->SetVelocity(Vec2(-PLAYER_RUN_SPEED, pRigid->GetVelocity().y));
	}
	if (KEY_PRESSED(KEY::RIGHT))
	{
		//pRigid->MovePosition(pPlayer->GetPos() + Vec2(400.f, 0.f) * fDT);
		pRigid->SetVelocity(Vec2(PLAYER_RUN_SPEED, pRigid->GetVelocity().y));
	}

	m_AccTime += fDT;

	if (m_AccTime >= m_Duration)
	{
		// Sound 재생 (발소리)
		CSound* pSound = CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\char\\char_mad_foot_00_dirt_01.wav");
		pSound->Play();

		// 누적 시간 초기화
		m_AccTime -= m_Duration;
	}


	// ### State 변경 ###

	// C키 입력 시 Jump State로 변경
	if (KEY_TAP(KEY::C) && pPlayer->CanJump())
	{
		GetStateMachine()->ChangeState(L"Jump");
	}
}
