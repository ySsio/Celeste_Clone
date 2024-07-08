#include "pch.h"
#include "CState_Jump.h"



CState_Jump::CState_Jump()
{
}

CState_Jump::~CState_Jump()
{
}

void CState_Jump::Jump()
{
	CPlayer* pPlayer = GetOwner();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	pRigid->SetVelocity(Vec2(pRigid->GetVelocity().x, -PLAYER_JUMP_SPEED));
	pRigid->SetGravityCoef(GRAVITY_COEF_JUMP);
}

void CState_Jump::EndJump()
{
	CPlayer* pPlayer = GetOwner();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	pRigid->SetVelocity(Vec2(pRigid->GetVelocity().x, 0.f));
	pRigid->SetGravityCoef(GRAVITY_COEF);

	GetStateMachine()->ChangeState(L"Fall");
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
	PlayAnimation();

	Jump();
}

void CState_Jump::Exit()
{
	CPlayer* pPlayer = GetOwner();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	pRigid->SetGravityCoef(GRAVITY_COEF);
}

void CState_Jump::FinalTick()
{
	CPlayer* pPlayer = GetOwner();
	Vec2 vDir = pPlayer->GetDir();
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
	Vec2 Velocity = pRigid->GetVelocity();
	if (fabs(Velocity.y) <= 5.f || KEY_RELEASED(KEY::C))
	{
		EndJump();
	}


}
