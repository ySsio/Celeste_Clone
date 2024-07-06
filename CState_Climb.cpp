#include "pch.h"
#include "CState_Climb.h"

#include "CTimeMgr.h"

CState_Climb::CState_Climb()
	: m_Warning(false)
	, m_ClimbDuration(4.f)
	, m_SlideWaitTime(1.5f)
	, m_AccTime(0.f)
{
}

CState_Climb::~CState_Climb()
{
}


void CState_Climb::PlayAnimation()
{
	Vec2 vDir = GetOwner()->GetDir();

	if (vDir.x == 1.f)
	{
		GetBangAnimator()->Play(L"Player_Bang_Climb", true);
		GetBodyAnimator()->Play(L"Player_Climb", true);
	}
	else if (vDir.x == -1.f)
	{
		GetBangAnimator()->Play(L"Player_Bang_Climb_FlipX", true);
		GetBodyAnimator()->Play(L"Player_Climb_FlipX", true);
	}
}

void CState_Climb::Slide(bool _Warning)
{
	CPlayer* pPlayer = GetOwner();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	// �߷��� �Ѽ� �������� ��
	pRigid->SetGravity(true);
	pRigid->SetMaxSpeed(PLAYER_SLIDE_SPEED);

	if (!_Warning)
	{
		// �ִϸ��̼� �����ؼ� �̲��������� ������
		GetBangAnimator()->Pause();
		GetBangAnimator()->Init();
		GetBodyAnimator()->Pause();
		GetBodyAnimator()->Init();
	}

}

void CState_Climb::Enter()
{
	PlayAnimation();

	CPlayer* pPlayer = GetOwner();
	CRigidBody* pRigid = pPlayer->GetRigidBody();
	pRigid->SetMaxSpeed(PLAYER_CLIMB_SPEED);
}

void CState_Climb::Exit()
{
	CPlayer* pPlayer = GetOwner();
	CRigidBody* pRigid = pPlayer->GetRigidBody();
	pPlayer->SetDirFix(false);
	pRigid->SetMaxSpeed(PLAYER_MAX_SPEED);
}

void CState_Climb::FinalTick()
{
	CPlayer* pPlayer = GetOwner();
	Vec2 vDir = GetOwner()->GetDir();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	// �ð� ����
	m_AccTime += fDT;
	
	// �ð��� ������ Warning ���·� ����
	if (m_AccTime >= m_ClimbDuration && !m_Warning)
	{
		m_Warning = true;

		pRigid->SetVelocity(Vec2(0.f, 0.f));

		// �ִϸ��̼� ����
		if (vDir.x == 1.f)
		{
			GetBangAnimator()->Pause();
			GetBodyAnimator()->Play(L"Player_Climb_Warning", true);
		}
		else if (vDir.x == -1.f)
		{
			GetBangAnimator()->Pause();
			GetBodyAnimator()->Play(L"Player_Climb_Warning_FlipX", true);
		}
	}

	// ZŰ ���� ���� �ٲ� �� �ֵ��� (������ ������ �� �ֵ���, �߷� �߰�)
	if (KEY_NONE(KEY::Z))
	{
		pPlayer->SetDirFix(false);
		
		Slide(false);
	}

	// Warning ������ �÷��̾ ��Ʈ���� �� ����
	if (!m_Warning)
	{
		// ZŰ�� ������ ������ ����
		if (KEY_PRESSED(KEY::Z))
		{
			// �÷��̾� ���� ����
			pPlayer->SetDirFix(true);

			pRigid->SetMaxSpeed(PLAYER_CLIMB_SPEED);
			pRigid->SetVelocity(Vec2(0.f, 0.f));
			pRigid->SetGravity(false);

			// Z�� ���� ���·� �� Ű�� ������ ��� �ö�
			if (KEY_PRESSED(KEY::UP))
			{
				pRigid->SetVelocity(Vec2(0.f, -PLAYER_CLIMB_SPEED));

				// �ö󰡸� ��ƿ �� �ִ� �ð� 2�� �ӵ��� ���� (�� �� �� ���������ν�)
				m_AccTime += fDT;
			}

			// Z�� ���� ���·� �Ʒ� Ű�� ������ ��� ������ (slide�� �ٸ�)
			if (KEY_PRESSED(KEY::DOWN))
			{
				pRigid->SetVelocity(Vec2(0.f, PLAYER_CLIMB_SPEED));
			}

			if (KEY_TAP(KEY::UP))
			{
				GetBangAnimator()->Resume();
				GetBodyAnimator()->Resume();
			}

			if (KEY_NONE(KEY::UP))
			{
				GetBangAnimator()->Pause();
				GetBangAnimator()->Init();
				GetBodyAnimator()->Pause();
				GetBodyAnimator()->Init();
			}
		}
	}
	else
	{
		// Warning ���� 
		
		// SlideWaitTime�� ������ Slide
		if (m_AccTime >= m_ClimbDuration + m_SlideWaitTime)
		{
			Slide(true);
		}
	}


	// ���� ������ �� �ʱ�ȭ (Enter)
	if (pPlayer->IsGround())
	{
		Enter();
	}

	

	// #### State ���� ####

	// ZŰ�� ���� fall state�� ����
	if (KEY_NONE(KEY::Z) && KEY_NONE(KEY::LEFT) && KEY_NONE(KEY::RIGHT) && KEY_NONE(KEY::Z))
	{
		GetStateMachine()->ChangeState(L"Fall");
	}
	 
	// CŰ �Է� �� Jump State�� ����
	if (KEY_TAP(KEY::C) && pPlayer->CanJump())
	{
		GetStateMachine()->ChangeState(L"Jump");
	}

	
}
