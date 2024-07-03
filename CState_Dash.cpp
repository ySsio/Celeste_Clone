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
}

void CState_Dash::FinalTick()
{
	CPlayer* pPlayer = GetOwner();
	Vec2 vDir = pPlayer->GetDir();
	CRigidBody* pRigid = pPlayer->GetRigidBody();

	m_AccTime += fDT;

	if (m_AccTime >= 0.05f && !m_FirstAfterImage)
	{
		m_FirstAfterImage = true;
		CAfterImage* pAfterImage = new CAfterImage(pPlayer->GetBuffer(), 0.5f);
		pAfterImage->SetPos(pPlayer->GetPos());
		CLevelMgr::Get()->GetCurLevel()->AddObject(pAfterImage, LAYER_TYPE::EFFECT);
	}
	if (m_AccTime >= 0.17f && !m_SecondAfterImage)
	{
		m_SecondAfterImage = true;
		CAfterImage* pAfterImage = new CAfterImage(pPlayer->GetBuffer(), 0.5f);
		pAfterImage->SetPos(pPlayer->GetPos());
		CLevelMgr::Get()->GetCurLevel()->AddObject(pAfterImage, LAYER_TYPE::EFFECT);
	}
	if (m_AccTime >= 0.29f && !m_ThirdAfterImage)
	{
		m_ThirdAfterImage = true;
		CAfterImage* pAfterImage = new CAfterImage(pPlayer->GetBuffer(), 0.5f);
		pAfterImage->SetPos(pPlayer->GetPos());
		CLevelMgr::Get()->GetCurLevel()->AddObject(pAfterImage, LAYER_TYPE::EFFECT);
	}

	if (KEY_TAP(KEY::X))
	{
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

}


