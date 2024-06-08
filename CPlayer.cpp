#include "pch.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSpriteRenderer.h"
#include "CAssetMgr.h"
#include "CAnimation.h"


CPlayer::CPlayer()
	: m_HeadSprite(nullptr)
	, m_HeadAnim(nullptr)
	, m_BodyAnim(nullptr)
	, m_Collider(nullptr)
{
	m_HeadAnim = AddComponent<CAnimator>();
	m_HeadAnim->AddAnimation(L"Player_Bang", CAssetMgr::Get()->FindAsset<CAnimation>(L"Player_Bang"));
	m_HeadAnim->AddAnimation(L"Player_Bang_FlipX", CAssetMgr::Get()->FindAsset<CAnimation>(L"Player_Bang_FlipX"));
	m_HeadAnim->Play(L"Player_Bang");

	m_BodyAnim = AddComponent<CAnimator>();
	m_BodyAnim->AddAnimation(L"Player_Idle", CAssetMgr::Get()->FindAsset<CAnimation>(L"Player_Idle"));
	m_BodyAnim->AddAnimation(L"Player_IdleA", CAssetMgr::Get()->FindAsset<CAnimation>(L"Player_IdleA"));
	m_BodyAnim->AddAnimation(L"Player_IdleB", CAssetMgr::Get()->FindAsset<CAnimation>(L"Player_IdleB"));
	m_BodyAnim->AddAnimation(L"Player_IdleC", CAssetMgr::Get()->FindAsset<CAnimation>(L"Player_IdleC"));
	m_BodyAnim->AddAnimation(L"Player_Idle_FlipX", CAssetMgr::Get()->FindAsset<CAnimation>(L"Player_Idle_FlipX"));
	m_BodyAnim->AddAnimation(L"Player_IdleA_FlipX", CAssetMgr::Get()->FindAsset<CAnimation>(L"Player_IdleA_FlipX"));
	m_BodyAnim->AddAnimation(L"Player_IdleB_FlipX", CAssetMgr::Get()->FindAsset<CAnimation>(L"Player_IdleB_FlipX"));
	m_BodyAnim->AddAnimation(L"Player_IdleC_FlipX", CAssetMgr::Get()->FindAsset<CAnimation>(L"Player_IdleC_FlipX"));
	m_BodyAnim->Play(L"Player_Idle");

	m_Collider = AddComponent<CCollider>();
	m_Collider->SetOffset(Vec2(0.f, 40.f));
	m_Collider->SetScale(Vec2(30.f, 50.f));
}

CPlayer::~CPlayer()
{
}

void CPlayer::Tick()
{
	Vec2 vPos = GetPos();

	
	if (KEY_PRESSED(KEY::LEFT))
	{
		vPos.x -= 300.f * fDT;
	}
	if (KEY_PRESSED(KEY::RIGHT))
	{
		vPos.x += 300.f * fDT;
	}

	if (KEY_TAP(KEY::LEFT))
	{
		if (m_HeadAnim)		
			m_HeadAnim->Play(L"Player_Bang_FlipX");
		if (m_BodyAnim)		
			m_BodyAnim->Play(L"Player_Idle_FlipX");
	}
	if (KEY_TAP(KEY::RIGHT))
	{
		if (m_HeadAnim)		
			m_HeadAnim->Play(L"Player_Bang");
		if (m_BodyAnim)		
			m_BodyAnim->Play(L"Player_Idle");
	}

	if (KEY_TAP(KEY::C))
	{
		// Jump

	}
	if (KEY_TAP(KEY::X))
	{
		// Dash

	}

	SetPos(vPos);
	
}

void CPlayer::Render()
{
	if (m_HeadAnim)
		m_HeadAnim->Render();

	if (m_BodyAnim)
		m_BodyAnim->Render();
}
