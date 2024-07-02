#include "pch.h"
#include "CState_Run.h"

CState_Run::CState_Run()
	: m_Dir(1.f)
{

}

CState_Run::~CState_Run()
{
}

void CState_Run::Enter()
{
	Vec2 vDir = GetOwner()->GetDir();
	m_Dir = vDir.x;

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

void CState_Run::FinalTick()
{
	CPlayer* pPlayer = GetOwner();
	Vec2 vDir = GetOwner()->GetDir();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	if (m_Dir != vDir.x)
	{
		m_Dir = vDir.x;

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
}
