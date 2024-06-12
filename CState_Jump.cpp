#include "pch.h"
#include "CState_Jump.h"



CState_Jump::CState_Jump()
{
}

CState_Jump::~CState_Jump()
{
}

void CState_Jump::Enter()
{
	CPlayer* pPlayer = GetOwner();
	Vec2 vDir = pPlayer->GetDir();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	pRigid->Jump();
	pRigid->SetGravity(true);
}

void CState_Jump::FinalTick()
{
	CPlayer* pPlayer = GetOwner();
	Vec2 vDir = pPlayer->GetDir();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	if (KEY_RELEASED(KEY::C))
	{
		pRigid->EndJump();
		GetStateMachine()->ChangeState(L"Fall");
	}
}
