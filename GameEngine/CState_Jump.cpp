#include "pch.h"
#include "CState_Jump.h"

#include "CSound.h"
#include "CAssetMgr.h"

CState_Jump::CState_Jump()
{
}

CState_Jump::~CState_Jump()
{
}

void CState_Jump::Jump()
{
	CPlayer* pPlayer = GetOwner();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	// 스태미나 감소 (6번 뛰면 모두 소진)
	pPlayer->DecreaseStamina(PLAYER_STAMINA / 6.f);

	// Sound 재생
	CSound* pSound = CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\char\\char_mad_jump.wav");
	pSound->Play();

	pRigid->SetVelocity(Vec2(pRigid->GetVelocity().x, -PLAYER_JUMP_SPEED));
	pRigid->SetGravity(true);
	pRigid->SetGravityCoef(GRAVITY_COEF_JUMP);
}

void CState_Jump::EndJump()
{
	CPlayer* pPlayer = GetOwner();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	pRigid->SetVelocity(Vec2(pRigid->GetVelocity().x, 0.f));
	pRigid->SetGravityCoef(GRAVITY_COEF);

	GetStateMachine()->ChangeState(L"Fall");
}

void CState_Jump::PlayAnimation()
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

void CState_Jump::Enter()
{
	PlayAnimation();	

	Jump();
}

void CState_Jump::Exit()
{
	CPlayer* pPlayer = GetOwner();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	pRigid->SetGravityCoef(GRAVITY_COEF);
}

void CState_Jump::FinalTick()
{
	CPlayer* pPlayer = GetOwner();
	Vec2 vDir = pPlayer->GetDir();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	if (KEY_PRESSED(KEY::LEFT))
	{
		pRigid->SetVelocity(Vec2(-PLAYER_RUN_SPEED, pRigid->GetVelocity().y));
	}
	if (KEY_PRESSED(KEY::RIGHT))
	{
		pRigid->SetVelocity(Vec2(PLAYER_RUN_SPEED, pRigid->GetVelocity().y));
	}

	if (pPlayer->IsDirChanged())
	{
		PlayAnimation();
	}

	


	// #### State 변경 ####

	// 일정 시간 지나면
	
	Vec2 Velocity = pRigid->GetVelocity();

	if (pRigid->GetVelocity().y > 0.f || KEY_RELEASED(KEY::C))
	{
		EndJump();
	}


}
