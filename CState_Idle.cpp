#include "pch.h"
#include "CState_Idle.h"




CState_Idle::CState_Idle()
{
	m_BangAnimList.push_back(L"Player_Bang_Idle");
	m_BangAnimList.push_back(L"Player_Bang_IdleA");
	m_BangAnimList.push_back(L"Player_Bang_IdleB");
	m_BangAnimList.push_back(L"Player_Bang_IdleC");

	m_BodyAnimList.push_back(L"Player_Idle");
	m_BodyAnimList.push_back(L"Player_IdleA");
	m_BodyAnimList.push_back(L"Player_IdleB");
	m_BodyAnimList.push_back(L"Player_IdleC");

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
	PlayAnimation();
}

void CState_Idle::FinalTick()
{
	CPlayer* pPlayer = GetOwner();

	if (GetBodyAnimator()->IsDone())
	{
		PlayAnimation();
	}

	// #### State 변경 ####

	pPlayer->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));

	// C키 입력 시 Jump State로 변경
	if (KEY_TAP(KEY::C))
	{
		GetStateMachine()->ChangeState(L"Jump");
	}

}

void CState_Idle::PlayAnimation()
{
	m_AnimPlayList.pop_front();

	int nextAnimIdx = m_AnimPlayList.front();

	wstring nextBangAnimName = m_BangAnimList[nextAnimIdx];
	wstring nextBodyAnimName = m_BodyAnimList[nextAnimIdx];

	if (GetOwner()->GetDir().x == -1.f)
	{
		nextBangAnimName += L"_FlipX";
		nextBodyAnimName += L"_FlipX";
	}

	GetBangAnimator()->Play(nextBangAnimName);
	GetBodyAnimator()->Play(nextBodyAnimName);

	// 애니메이션 플레이리스트에 랜덤으로 하나를 추가한다.
	m_AnimPlayList.push_back(rand() % m_BodyAnimList.size());
}
