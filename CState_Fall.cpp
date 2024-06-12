#include "pch.h"
#include "CState_Fall.h"



CState_Fall::CState_Fall()
{
}

CState_Fall::~CState_Fall()
{
}

void CState_Fall::Enter()
{
}

void CState_Fall::FinalTick()
{
	CPlayer* pPlayer = GetOwner();
	CAnimator* pAnim = pPlayer->GetComponent<CAnimator>();
	float Dir = pPlayer->GetDir().x;

	wstring AnimName = L"falling animation";

	if (Dir<0.f)
	{
		AnimName += L"_FlipX";
	}

	pAnim->Play(AnimName);
	
}
