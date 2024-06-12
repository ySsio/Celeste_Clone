#include "pch.h"
#include "CState_Run.h"

CState_Run::CState_Run()
{
}

CState_Run::~CState_Run()
{
}

void CState_Run::Enter()
{
}

void CState_Run::FinalTick()
{
	CPlayer* pPlayer = GetOwner();
	Vec2 vDir = pPlayer->GetDir();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	if (KEY_PRESSED(KEY::LEFT))
	{
		pRigid->MovePosition(pPlayer->GetPos() + Vec2(-400.f, 0.f) * fDT);

	}
	if (KEY_PRESSED(KEY::RIGHT))
	{
		pRigid->MovePosition(pPlayer->GetPos() + Vec2(400.f, 0.f) * fDT);
	}


	// ### State º¯°æ ###
	if (KEY_TAP(KEY::C))
	{
		GetStateMachine()->ChangeState(L"Jump");
	}
	if (KEY_NONE(KEY::LEFT) && KEY_NONE(KEY::RIGHT))
	{
		GetStateMachine()->ChangeState(L"Idle");
	}
}
