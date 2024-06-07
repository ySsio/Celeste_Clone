#include "pch.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CSpriteRenderer.h"
#include "CAssetMgr.h"

CPlayer::CPlayer()
	: m_HeadSprite(nullptr)
	, m_BodySprite(nullptr)
	, m_HeadAnim(nullptr)
	, m_BodyAnim(nullptr)
{
	m_HeadSprite = new CSpriteRenderer;
	m_HeadSprite->SetOwner(this);
	m_HeadSprite->SetTexture(CAssetMgr::Get()->LoadAsset<CTexture>(L"PlayerHead", L"\\texture\\Player\\bangs00.png")->Scale(4.f));
	m_HeadSprite->SetOffset(Vec2(0.f, 20.f));

	m_BodySprite = new CSpriteRenderer;
	m_BodySprite->SetOwner(this);
	m_BodySprite->SetTexture(CAssetMgr::Get()->LoadAsset<CTexture>(L"PlayerBody", L"\\texture\\Player\\idle00.png")->Scale(4.f));

}

CPlayer::~CPlayer()
{
}

void CPlayer::Tick()
{
	Vec2 vPos = GetPos();

	if (KEY_PRESSED(KEY::W))
	{
		vPos.y -= 300.f * fDT;
	}
	if (KEY_PRESSED(KEY::A))
	{
		vPos.x -= 300.f * fDT;
	}
	if (KEY_PRESSED(KEY::S))
	{
		vPos.y += 300.f * fDT;
	}
	if (KEY_PRESSED(KEY::D))
	{
		vPos.x += 300.f * fDT;
	}


	SetPos(vPos);
}

void CPlayer::Render()
{
	if (m_HeadSprite)
		m_HeadSprite->Render();

	if (m_BodySprite)
		m_BodySprite->Render();
		
}
