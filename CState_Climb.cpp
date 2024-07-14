#include "pch.h"
#include "CState_Climb.h"

#include "CTimeMgr.h"

CState_Climb::CState_Climb()
	: m_Warning(false)
	, m_SlideWaitTime(1.f)
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

	GetBangAnimator()->Init();
	GetBangAnimator()->Pause();

	if (!_Warning)
	{
		// �ִϸ��̼� �����ؼ� �̲��������� ������
		GetBodyAnimator()->Init();
		GetBodyAnimator()->Pause();
	}

}

void CState_Climb::Enter()
{
	PlayAnimation();

	// ���� �ʱ�ȭ
	m_Warning = false;
	m_AccTime = 0.f;

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
	pRigid->SetGravity(true);
}

void CState_Climb::FinalTick()
{
	CPlayer* pPlayer = GetOwner();
	Vec2 vDir = GetOwner()->GetDir();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	// ���¹̳� ����
	pPlayer->DecreaseStamina(PLAYER_STAMINA / 4.f * fDT);
	
	// ���¹̳� 0 �Ǹ� Warning ���·� ����
	if (pPlayer->GetStamina() <= 0.f && !m_Warning)
	{
		m_Warning = true;

		pRigid->SetVelocity(Vec2(0.f, 0.f));

		GetBangAnimator()->Init();
		GetBangAnimator()->Pause();

		// �ִϸ��̼� ����
		if (vDir.x == 1.f)
		{
			GetBodyAnimator()->Play(L"Player_Climb_Warning", true);
		}
		else if (vDir.x == -1.f)
		{
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
		if(KEY_PRESSED(KEY::Z))
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

				// �ö󰡸� ��ƿ �� �ִ� �ð� 2�� �ӵ��� ���� (�� �� �� ���¹̳��� ����)
				pPlayer->DecreaseStamina(PLAYER_STAMINA / 4.f * fDT);
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
				GetBangAnimator()->Init();
				GetBangAnimator()->Pause();
				GetBodyAnimator()->Init();
				GetBodyAnimator()->Pause();
			}
		}
	}
	else
	{
		// Warning ���� 
		m_AccTime += fDT;
		
		// SlideWaitTime�� ������ Slide
		if (m_AccTime >= m_SlideWaitTime)
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
	 
	// Warning �ƴ� ��, CŰ �Է� �� Jump State�� ����
	if (!m_Warning && KEY_TAP(KEY::C) && pPlayer->CanJump())
	{
		GetStateMachine()->ChangeState(L"Jump");
	}

	
}
