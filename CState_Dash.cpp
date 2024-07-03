#include "pch.h"
#include "CState_Dash.h"

CState_Dash::CState_Dash()
{
}

CState_Dash::~CState_Dash()
{
}

void CState_Dash::PlayAnimation()
{
	Vec2 vDir = GetOwner()->GetDir();

	if (vDir.x == 1.f)
	{
		GetBangAnimator()->Play(L"Player_Bang_Dash", true);
		GetBodyAnimator()->Play(L"Player_Dash", true);
	}
	else if (vDir.x == -1.f)
	{
		GetBangAnimator()->Play(L"Player_Bang_Dash_FlipX", true);
		GetBodyAnimator()->Play(L"Player_Dash_FlipX", true);
	}
}

void CState_Dash::Enter()
{
	PlayAnimation();
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


