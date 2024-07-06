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

	// 중력을 켜서 떨어지게 함
	pRigid->SetGravity(true);
	pRigid->SetMaxSpeed(PLAYER_SLIDE_SPEED);

	if (!_Warning)
	{
		// 애니메이션 고정해서 미끄러지듯이 내려감
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

	// 시간 누적
	m_AccTime += fDT;
	
	// 시간이 지나면 Warning 상태로 진입
	if (m_AccTime >= m_ClimbDuration && !m_Warning)
	{
		m_Warning = true;

		pRigid->SetVelocity(Vec2(0.f, 0.f));

		// 애니메이션 변경
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

	// Z키 떼면 방향 바꿀 수 있도록 (벽에서 떨어질 수 있도록, 중력 추가)
	if (KEY_NONE(KEY::Z))
	{
		pPlayer->SetDirFix(false);
		
		Slide(false);
	}

	// Warning 전까지 플레이어가 컨트롤할 수 있음
	if (!m_Warning)
	{
		// Z키를 누르고 있으면 고정
		if (KEY_PRESSED(KEY::Z))
		{
			// 플레이어 방향 고정
			pPlayer->SetDirFix(true);

			pRigid->SetMaxSpeed(PLAYER_CLIMB_SPEED);
			pRigid->SetVelocity(Vec2(0.f, 0.f));
			pRigid->SetGravity(false);

			// Z를 누른 상태로 위 키를 누르면 기어 올라감
			if (KEY_PRESSED(KEY::UP))
			{
				pRigid->SetVelocity(Vec2(0.f, -PLAYER_CLIMB_SPEED));

				// 올라가면 버틸 수 있는 시간 2배 속도로 감소 (한 번 더 더해줌으로써)
				m_AccTime += fDT;
			}

			// Z를 누른 상태로 아래 키를 누르면 기어 내려감 (slide와 다름)
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
		// Warning 진입 
		
		// SlideWaitTime이 지나면 Slide
		if (m_AccTime >= m_ClimbDuration + m_SlideWaitTime)
		{
			Slide(true);
		}
	}


	// 땅에 닿으면 다 초기화 (Enter)
	if (pPlayer->IsGround())
	{
		Enter();
	}

	

	// #### State 변경 ####

	// Z키를 떼면 fall state로 변경
	if (KEY_NONE(KEY::Z) && KEY_NONE(KEY::LEFT) && KEY_NONE(KEY::RIGHT) && KEY_NONE(KEY::Z))
	{
		GetStateMachine()->ChangeState(L"Fall");
	}
	 
	// C키 입력 시 Jump State로 변경
	if (KEY_TAP(KEY::C) && pPlayer->CanJump())
	{
		GetStateMachine()->ChangeState(L"Jump");
	}

	
}
