#include "pch.h"
#include "CState_Idle.h"


#define IDLE_ANIM_LIST_COUNT 10

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

	for (int i = 0; i < IDLE_ANIM_LIST_COUNT; ++i)
	{
		m_AnimPlayList.push_back(0);
	}
}

CState_Idle::~CState_Idle()
{
}

void CState_Idle::Enter()
{
	for (auto iter = m_AnimPlayList.begin(); iter != m_AnimPlayList.end(); ++iter)
	{
		*iter = 0;
	}

	PlayAnimation();
}

void CState_Idle::Exit()
{
}

void CState_Idle::FinalTick()
{
	CPlayer* pPlayer = GetOwner();

	if (GetBodyAnimator()->IsDone())
	{
		PlayAnimation();
	}

	// 속도를 0으로 설정
	pPlayer->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));


	// #### State 변경 ####

	// Run State : 좌우키 눌려있으면
	if (KEY_PRESSED(KEY::LEFT) || KEY_PRESSED(KEY::RIGHT))
	{
		GetStateMachine()->ChangeState(L"Run");
	}

	// C키 입력 시 Jump State로 변경
	if (KEY_TAP(KEY::C) && pPlayer->CanJump())
	{
		GetStateMachine()->ChangeState(L"Jump");
	}

}

void CState_Idle::PlayAnimation()
{
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

	// 플레이한 애니메이션은 리스트에서 제거
	m_AnimPlayList.pop_front();

	// 플레이리스트가 비면 IDLE_ANIM_LIST_COUNT개를 다시 채움
	// 랜덤 0 0 0 0 랜덤 0 0 0 0꼴로
	if (m_AnimPlayList.empty())
	{
		m_AnimPlayList.push_back(rand() % m_BodyAnimList.size());
		m_AnimPlayList.push_back(0);
		m_AnimPlayList.push_back(0);
		m_AnimPlayList.push_back(0);
		m_AnimPlayList.push_back(0);
		m_AnimPlayList.push_back(rand() % m_BodyAnimList.size());
		m_AnimPlayList.push_back(0);
		m_AnimPlayList.push_back(0);
		m_AnimPlayList.push_back(0);
		m_AnimPlayList.push_back(0);
	}
}
