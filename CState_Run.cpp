#include "pch.h"
#include "CState_Run.h"

CState_Run::CState_Run()
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
		pRigid->SetVelocity(Vec2(-400.f, pRigid->GetVelocity().y));

	}
	if (KEY_PRESSED(KEY::RIGHT))
	{
		//pRigid->MovePosition(pPlayer->GetPos() + Vec2(400.f, 0.f) * fDT);
		pRigid->SetVelocity(Vec2(400.f, pRigid->GetVelocity().y));
	}

	// ### State º¯°æ ###
	if (KEY_TAP(KEY::C))
	{
		GetStateMachine()->ChangeState(L"Jump");
	}
}
