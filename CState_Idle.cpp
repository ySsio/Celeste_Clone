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

	// �ӵ��� 0���� ����
	pPlayer->GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));


	// #### State ���� ####

	// Run State : �¿�Ű ����������
	if (KEY_PRESSED(KEY::LEFT) || KEY_PRESSED(KEY::RIGHT))
	{
		GetStateMachine()->ChangeState(L"Run");
	}

	// CŰ �Է� �� Jump State�� ����
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

	// �÷����� �ִϸ��̼��� ����Ʈ���� ����
	m_AnimPlayList.pop_front();

	// �÷��̸���Ʈ�� ��� IDLE_ANIM_LIST_COUNT���� �ٽ� ä��
	// ���� 0 0 0 0 ���� 0 0 0 0�÷�
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
