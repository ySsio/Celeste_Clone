#include "pch.h"
#include "CState_Dash.h"

#include "CAfterImage.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CSound.h"
#include "CAssetMgr.h"

CState_Dash::CState_Dash()
	: m_AccTime(0.f)
	, m_FirstAfterImage(false)
	, m_SecondAfterImage(false)
	, m_ThirdAfterImage(false)
	, m_DashSpeed(1260.f)
	, m_AfterImageColor(ALPHA_HALF)
{
}

CState_Dash::~CState_Dash()
{
}

void CState_Dash::Dash()
{
	CPlayer* pPlayer = GetOwner();
	Vec2 vDir = pPlayer->GetDir();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	if (pPlayer->GetDashCount() == 0)
		return;

	if (vDir.y != 0.f)
	{
		if (KEY_NONE(KEY::LEFT) && KEY_NONE(KEY::RIGHT))
		{
			vDir.x = 0.f;
		}
	}

	// Dash
	pRigid->SetSpeedLimit(false);
	pRigid->SetFrictionCoef(FRICTION_DASH);
	pRigid->SetFrictionY(true);
	pRigid->SetGravity(false);

	pPlayer->SubtractDashCount();

	pRigid->SetVelocity(vDir.Normalize() * m_DashSpeed);
}

void CState_Dash::PlayAnimation()
{
	Vec2 vDir = GetOwner()->GetDir();

	if (vDir.x == 1.f)
	{
		GetBangAnimator()->Play(L"Player_Bang_Dash", true);
		GetBodyAnimator()->Play(L"Player_Dash", true);
	}
	else if (vDir.x == -1.f)
	{
		GetBangAnimator()->Play(L"Player_Bang_Dash_FlipX", true);
		GetBodyAnimator()->Play(L"Player_Dash_FlipX", true);
	}
}

void CState_Dash::Enter()
{
	// 변수 초기화
	m_AccTime = 0.f;
	m_FirstAfterImage = false;
	m_SecondAfterImage = false;
	m_ThirdAfterImage = false;

	// 애니메이션 재생
	PlayAnimation();

	// Sound 재생
	CSound* pSound = CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\char\\char_mad_dash_red_left.wav");
	pSound->Play();

	// 대쉬
	Dash();


	// 잔상 색깔 결정
	m_AfterImageColor = ALPHA_HALF;

	if (GetOwner()->GetDashCount() >= 1)
		m_AfterImageColor |= RED_BANG;
	else
		m_AfterImageColor |= BLUE_BANG;
	
}

void CState_Dash::Exit()
{
	CPlayer* pPlayer = GetOwner();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	pRigid->SetSpeedLimit(true);
	pRigid->SetFrictionCoef(FRICTION);
	pRigid->SetFrictionY(false);
 	pRigid->SetGravity(true);
}

void CState_Dash::FinalTick()
{
	CPlayer* pPlayer = GetOwner();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	m_AccTime += fDT;

	if (m_AccTime >= 0.01f && !m_FirstAfterImage)
	{
		m_FirstAfterImage = true;
		CAfterImage* pAfterImage = new CAfterImage(pPlayer->GetBuffer(), 0.5f);
		pAfterImage->SetPos(pPlayer->GetPos());
		pAfterImage->SetRGBA(m_AfterImageColor);
		Add_Object(pAfterImage, LAYER_TYPE::PLAYER_EFFECT);
	}
	if (m_AccTime >= 0.1f && !m_SecondAfterImage)
	{
		m_SecondAfterImage = true;
		CAfterImage* pAfterImage = new CAfterImage(pPlayer->GetBuffer(), 0.5f);
		pAfterImage->SetPos(pPlayer->GetPos());
		pAfterImage->SetRGBA(m_AfterImageColor);
		Add_Object(pAfterImage, LAYER_TYPE::PLAYER_EFFECT);
	}
	if (m_AccTime >= 0.2f && !m_ThirdAfterImage)
	{
		m_ThirdAfterImage = true;
		CAfterImage* pAfterImage = new CAfterImage(pPlayer->GetBuffer(), 0.5f);
		pAfterImage->SetPos(pPlayer->GetPos());
		pAfterImage->SetRGBA(m_AfterImageColor);
		Add_Object(pAfterImage, LAYER_TYPE::PLAYER_EFFECT);
	}

	// 대쉬 시간이 지나면 대쉬 종료
	if (m_AccTime >= DASH_TIME)
	{
		GetStateMachine()->ChangeState(L"Fall");
	}

}


