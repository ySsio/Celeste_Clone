#include "pch.h"
#include "CState_Fall.h"



CState_Fall::CState_Fall()
{
}

CState_Fall::~CState_Fall()
{
}

void CState_Fall::PlayAnimation()
{
	Vec2 vDir = GetOwner()->GetDir();

	if (vDir.x == 1.f)
	{
		GetBangAnimator()->Play(L"Player_Bang_Fall");
		GetBodyAnimator()->Play(L"Player_Fall");
	}
	else if (vDir.x == -1.f)
	{
		GetBangAnimator()->Play(L"Player_Bang_Fall_FlipX");
		GetBodyAnimator()->Play(L"Player_Fall_FlipX");
	}
}

void CState_Fall::Enter()
{
	PlayAnimation();

	CPlayer* pPlayer = GetOwner();
	CRigidBody* pRigid = pPlayer->GetRigidBody();
}

void CState_Fall::Exit()
{
}

void CState_Fall::FinalTick()
{
	CPlayer* pPlayer = GetOwner();
	Vec2 vDir = GetOwner()->GetDir();

	CRigidBody* pRigid = pPlayer->GetRigidBody();

	
	if (KEY_PRESSED(KEY::LEFT))
	{
		pRigid->SetVelocity(Vec2(-PLAYER_RUN_SPEED, pRigid->GetVelocity().y));

	}
	if (KEY_PRESSED(KEY::RIGHT))
	{
		pRigid->SetVelocity(Vec2(PLAYER_RUN_SPEED, pRigid->GetVelocity().y));
	}


	if (pPlayer->IsDirChanged())
	{
		PlayAnimation();
	}



	// #### State º¯°æ ####
	if (pPlayer->IsGround())
	{
		GetStateMachine()->ChangeState(L"Idle");
	}
	
}
