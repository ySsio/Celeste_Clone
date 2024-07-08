#include "pch.h"
#include "CState_Bounce.h"



CState_Bounce::CState_Bounce()
	: m_BounceSpeed(PLAYER_BOUNCE_SPEED)
{
}

CState_Bounce::~CState_Bounce()
{
}

void CState_Bounce::PlayAnimation()
{
	Vec2 vDir = GetOwner()->GetDir();

	if (vDir.x == 1.f)
	{
		GetBangAnimator()->Play(L"Player_Bang_Jump");
		GetBodyAnimator()->Play(L"Player_Jump");
	}
	else if (vDir.x == -1.f)
	{
		GetBangAnimator()->Play(L"Player_Bang_Jump_FlipX");
		GetBodyAnimator()->Play(L"Player_Jump_FlipX");
	}
}

void CState_Bounce::Enter()
{
	PlayAnimation();

	CPlayer* pPlayer = GetOwner();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	pPlayer->ResetDash();
	pRigid->SetMaxSpeed(PLAYER_BOUNCE_SPEED);

	Vec2 Vel = pRigid->GetVelocity();

	// 설정된 방향으로 BounceSpeed만큼의 속력으로 설정
	if (m_Dir.x)
	{
		Vel = Vec2(m_Dir.x * m_BounceSpeed, Vel.y);
	}
	else if (m_Dir.y)
	{
		Vel = Vec2(0.f, m_Dir.y * m_BounceSpeed);
	}

	pRigid->SetVelocity(Vel);
}

void CState_Bounce::Exit()
{
	CPlayer* pPlayer = GetOwner();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	pRigid->SetMaxSpeed(PLAYER_MAX_SPEED);
}

void CState_Bounce::FinalTick()
{
	CPlayer* pPlayer = GetOwner();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	if (KEY_PRESSED(KEY::LEFT))
	{
		//pRigid->MovePosition(pPlayer->GetPos() + Vec2(-400.f, 0.f) * fDT);
		pRigid->SetVelocity(Vec2(-PLAYER_RUN_SPEED, pRigid->GetVelocity().y));
	}
	if (KEY_PRESSED(KEY::RIGHT))
	{
		//pRigid->MovePosition(pPlayer->GetPos() + Vec2(400.f, 0.f) * fDT);
		pRigid->SetVelocity(Vec2(PLAYER_RUN_SPEED, pRigid->GetVelocity().y));
	}

	if (pPlayer->IsDirChanged())
	{
		PlayAnimation();
	}
}