#include "pch.h"
#include "CState_Dash.h"

#include "CAfterImage.h"

#include "CLevelMgr.h"
#include "CLevel.h"

CState_Dash::CState_Dash()
	: m_AccTime(0.f)
	, m_FirstAfterImage(false)
	, m_SecondAfterImage(false)
	, m_ThirdAfterImage(false)
{
}

CState_Dash::~CState_Dash()
{
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
	PlayAnimation();
	m_AccTime = 0.f;
	m_FirstAfterImage = false;
	m_SecondAfterImage = false;
	m_ThirdAfterImage = false;

	CPlayer* pPlayer = GetOwner();
	Vec2 vDir = pPlayer->GetDir();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	if (vDir.y != 0.f)
	{
		if (KEY_NONE(KEY::LEFT) && KEY_NONE(KEY::RIGHT))
		{
			vDir.x = 0.f;
		}
	}

	// Dash
	pRigid->Dash(vDir);
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
		Add_Object(pAfterImage, LAYER_TYPE::PLAYER_EFFECT);
	}
	if (m_AccTime >= 0.1f && !m_SecondAfterImage)
	{
		m_SecondAfterImage = true;
		CAfterImage* pAfterImage = new CAfterImage(pPlayer->GetBuffer(), 0.5f);
		pAfterImage->SetPos(pPlayer->GetPos());
		Add_Object(pAfterImage, LAYER_TYPE::PLAYER_EFFECT);
	}
	if (m_AccTime >= 0.19f && !m_ThirdAfterImage)
	{
		m_ThirdAfterImage = true;
		CAfterImage* pAfterImage = new CAfterImage(pPlayer->GetBuffer(), 0.5f);
		pAfterImage->SetPos(pPlayer->GetPos());
		Add_Object(pAfterImage, LAYER_TYPE::PLAYER_EFFECT);
	}

	if (m_AccTime >= DASH_TIME)
	{
		GetStateMachine()->ChangeState(L"Fall");
	}

}


