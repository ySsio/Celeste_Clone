#include "pch.h"
#include "CSpring.h"

#include "CAssetMgr.h"

#include "CPlayer.h"
#include "CRigidBody.h"

CSpring::CSpring()
	: m_Animator(nullptr)
	, m_Dir(Vec2(0.f,-1.f))
{
	m_Animator = AddComponent<CAnimator>();
	m_Animator->AddAnimation(L"Spring_Idle", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Spring_Idle.anim"));
	m_Animator->AddAnimation(L"Spring_Active", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Spring_Active.anim"));
	m_Animator->Play(L"Spring_Idle", true);

	m_Collider = AddComponent<CCollider>();
	m_Collider->SetOffset(Vec2(0.f, 30.f));
	m_Collider->SetScale(Vec2(80.f, 20.f));
}

CSpring::~CSpring()
{
}

void CSpring::Tick()
{
	if (m_Animator->IsDone())
		m_Animator->Play(L"Spring_Idle", true);
}

void CSpring::Render()
{
	if (m_Animator)
		m_Animator->Render();
}

void CSpring::OnCollisionEnter(CCollider* _Col, CObj* _Other, CCollider* _OtherCol)
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(_Other);

	if (pPlayer && _OtherCol == pPlayer->GetCollider())
	{
		// Active 애니메이션 재생
		m_Animator->Play(L"Spring_Active");


	}
}