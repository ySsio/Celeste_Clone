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

	// 중력을 켜서 떨어지게 함
	pRigid->SetGravity(true);
	pRigid->SetMaxSpeed(PLAYER_SLIDE_SPEED);

	GetBangAnimator()->Init();
	GetBangAnimator()->Pause();

	if (!_Warning)
	{
		// 애니메이션 고정해서 미끄러지듯이 내려감
		GetBodyAnimator()->Init();
		GetBodyAnimator()->Pause();
	}

}

void CState_Climb::Enter()
{
	PlayAnimation();

	// 변수 초기화
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

	// 스태미나 감소
	pPlayer->DecreaseStamina(PLAYER_STAMINA / 4.f * fDT);
	
	// 스태미나 0 되면 Warning 상태로 진입
	if (pPlayer->GetStamina() <= 0.f && !m_Warning)
	{
		m_Warning = true;

		pRigid->SetVelocity(Vec2(0.f, 0.f));

		GetBangAnimator()->Init();
		GetBangAnimator()->Pause();

		// 애니메이션 변경
		if (vDir.x == 1.f)
		{
			GetBodyAnimator()->Play(L"Player_Climb_Warning", true);
		}
		else if (vDir.x == -1.f)
		{
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
		if(KEY_PRESSED(KEY::Z))
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

				// 올라가면 버틸 수 있는 시간 2배 속도로 감소 (한 번 더 스태미나를 빼줌)
				pPlayer->DecreaseStamina(PLAYER_STAMINA / 4.f * fDT);
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
				GetBangAnimator()->Init();
				GetBangAnimator()->Pause();
				GetBodyAnimator()->Init();
				GetBodyAnimator()->Pause();
			}
		}
	}
	else
	{
		// Warning 진입 
		m_AccTime += fDT;
		
		// SlideWaitTime이 지나면 Slide
		if (m_AccTime >= m_SlideWaitTime)
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
	 
	// Warning 아닐 때, C키 입력 시 Jump State로 변경
	if (!m_Warning && KEY_TAP(KEY::C) && pPlayer->CanJump())
	{
		GetStateMachine()->ChangeState(L"Jump");
	}

	
}
