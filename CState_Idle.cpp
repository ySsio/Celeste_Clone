#include "pch.h"
#include "CState_Idle.h"




CState_Idle::CState_Idle()
	: m_curAnimDuration(0.f)
	, m_AccTime(0.f)
{
	m_AnimList.push_back(L"Player_Idle");
	m_AnimList.push_back(L"Player_IdleA");
	m_AnimList.push_back(L"Player_IdleB");
	m_AnimList.push_back(L"Player_IdleC");

	for (int i = 0; i < 6; ++i)
	{
		m_AnimPlayList.push_back(0);
	}
}

CState_Idle::~CState_Idle()
{
}

void CState_Idle::Enter()
{
}

void CState_Idle::FinalTick()
{
	CPlayer* pPlayer = GetOwner();
	CAnimator* pAnim = pPlayer->GetComponent<CAnimator>();

	m_AccTime += fDT;

	// Random Animation 재생
	if (m_curAnimDuration <= m_AccTime)
	{
		PlayNextAnim();
	}


	// #### State 변경 ####
	
	// 좌/우 키 입력 시 Run State로 변경
	if (KEY_TAP(KEY::LEFT) || KEY_TAP(KEY::RIGHT))
	{
		GetStateMachine()->ChangeState(L"Run");
	}
	// C키 입력 시 Jump State로 변경
	if (KEY_TAP(KEY::C))
	{
		GetStateMachine()->ChangeState(L"Jump");
	}

}

void CState_Idle::PlayNextAnim()
{
	m_AnimPlayList.pop_front();

	int nextAnimIdx = m_AnimPlayList.front();

	wstring nextAnimName = m_AnimList[nextAnimIdx];

	if (GetOwner()->GetDir().x == -1.f)
		nextAnimName += L"_FlipX";

	m_curAnimDuration = GetAnimator()->Play(nextAnimName);
	m_AccTime = 0.f;
	m_AnimPlayList.push_back(rand() % m_AnimList.size());
}
