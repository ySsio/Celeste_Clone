#include "pch.h"
#include "CState_Dash.h"

CState_Dash::CState_Dash()
{
}

CState_Dash::~CState_Dash()
{
}

void CState_Dash::Enter()
{
}

void CState_Dash::FinalTick()
{
	CPlayer* pPlayer = GetOwner();
	Vec2 vDir = pPlayer->GetDir();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	if (KEY_TAP(KEY::X))
	{
		if (vDir.y != 0.f)
		{
			if (KEY_NONE(KEY::LEFT) && KEY_NONE(KEY::RIGHT))
			{
				vDir.x = 0.f;
			}
		}

		// Dash
		pRigid->Dash(vDir);
	}

}


