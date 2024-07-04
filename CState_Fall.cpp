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
}

void CState_Fall::Enter()
{
	Vec2 vDir = GetOwner()->GetDir();

	if (vDir.x == 1.f)
	{
		GetBangAnimator()->Play(L"Player_Bang_Fall", true);
		GetBodyAnimator()->Play(L"Player_Fall", true);
	}
	else if (vDir.x == -1.f)
	{
		GetBangAnimator()->Play(L"Player_Bang_Fall_FlipX", true);
		GetBodyAnimator()->Play(L"Player_Fall_FlipX", true);
	}
}

void CState_Fall::FinalTick()
{
	CPlayer* pPlayer = GetOwner();
	Vec2 vDir = GetOwner()->GetDir();

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

	if (vDir.x == 1.f)
	{
		GetBangAnimator()->Play(L"Player_Bang_Fall", true);
		GetBodyAnimator()->Play(L"Player_Fall", true);
	}
	else if (vDir.x == -1.f)
	{
		GetBangAnimator()->Play(L"Player_Bang_Fall_FlipX", true);
		GetBodyAnimator()->Play(L"Player_Fall_FlipX", true);
	}

	// #### State º¯°æ ####

	// ¶¥¿¡ ´êÀ¸¸é Idle state·Î º¯°æ
	if (pRigid->IsGround())
	{
		GetStateMachine()->ChangeState(L"Idle");
	}
	
}
