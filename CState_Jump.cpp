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
	CRigidBody* pRigid = GetRigidBody();

	pRigid->Jump();
	pRigid->SetGravity(true);
}

void CState_Jump::FinalTick()
{
	CRigidBody* pRigid = GetRigidBody();

	if (KEY_RELEASED(KEY::C))
	{
		pRigid->EndJump();
	}
}
