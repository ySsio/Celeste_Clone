#include "pch.h"
#include "CState_Jump.h"



CState_Jump::CState_Jump()
{
}

CState_Jump::~CState_Jump()
{
}

void CState_Jump::PlayAnimation()
{
	Vec2 vDir = GetOwner()->GetDir();

	if (vDir.x == 1.f)
	{
		GetBangAnimator()->Play(L"Player_Bang_Jump");
		GetBodyAnimator()->Play(L"Player_Jump");
	}
	else if (vDir.x == -1.f)
	{
		GetBangAnimator()->Play(L"Player_Bang_Jump_FlipX");
		GetBodyAnimator()->Play(L"Player_Jump_FlipX");
	}
}

void CState_Jump::Enter()
{
	CPlayer* pPlayer = GetOwner();
	
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	pRigid->Jump();
	pRigid->SetGravity(true);

	PlayAnimation();
}

void CState_Jump::FinalTick()
{
	CPlayer* pPlayer = GetOwner();
	Vec2 vDir = pPlayer->GetDir();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	if (KEY_PRESSED(KEY::LEFT))
	{
		//pRigid->MovePosition(pPlayer->GetPos() + Vec2(-400.f, 0.f) * fDT);
		pRigid->SetVelocity(Vec2(-PLAYER_SPEED, pRigid->GetVelocity().y));

	}
	if (KEY_PRESSED(KEY::RIGHT))
	{
		//pRigid->MovePosition(pPlayer->GetPos() + Vec2(400.f, 0.f) * fDT);
		pRigid->SetVelocity(Vec2(PLAYER_SPEED, pRigid->GetVelocity().y));
	}

	if (pPlayer->IsDirChanged())
	{
		PlayAnimation();
	}


	// #### State 변경 ####

	// C키를 떼면 점프를 종료하고 Fall state로 변경
	if (KEY_RELEASED(KEY::C))
	{
		pRigid->EndJump();
		GetStateMachine()->ChangeState(L"Fall");
	}

}
