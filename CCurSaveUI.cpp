#include "pch.h"
#include "CCurSaveUI.h"

#include "CEngine.h"
#include "CAssetMgr.h"
#include "CGameMgr.h"

#include "CImageUI.h"
#include "CAnimUI.h"
#include "CTextUI.h"

CCurSaveUI::CCurSaveUI()
	: m_SaveData(nullptr)
{
	SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\FileSelect\\ticket.png")->Scale(0.9f));

	CImageUI* pCard = new CImageUI;
	pCard->SetPos(Vec2(0.f, 0.f));
	pCard->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\FileSelect\\card.png")->Scale(0.9f));
	pCard->SetTexOffset(Vec2(0.f, 0.f));
	AddChild(pCard);

	CAnimUI* pPortrait = new CAnimUI;
	pPortrait->SetPos(Vec2(-200.f, 0.f));
	pPortrait->SetAnim(L"Madeliene_Portrait", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Portrait.anim"));
	pCard->AddChild(pPortrait);

	CImageUI* pImage = new CImageUI;
	pImage->SetPos(Vec2(-200.f, 0.f));
	pImage->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\FileSelect\\portraitOverlay.png")->Scale(0.9f));
	pCard->AddChild(pImage);

	pImage = new CImageUI;
	pImage->SetPos(Vec2(50.f, 50.f));
	pImage->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\collectables\\strawberry.png")->Scale(0.9f));
	pCard->AddChild(pImage);

	CTextUI* pTextUI = new CTextUI;
	pTextUI->SetPos(Vec2(50.f, -80.f));
	pTextUI->SetText(L"¸Åµé¸°");
	pTextUI->SetFont(L"³ª´®°íµñ", 40);
	pCard->AddChild(pTextUI);

	pTextUI = new CTextUI;
	pTextUI->SetPos(Vec2(50.f, -40.f));
	pTextUI->SetText(L"ÄÚ¾î");
	pTextUI->SetFont(L"³ª´®°íµñ", 30);
	pCard->AddChild(pTextUI);
}

CCurSaveUI::CCurSaveUI(const CCurSaveUI& _Other)
	: CButtonUI(_Other)
	, m_SaveData(nullptr)
{
}

CCurSaveUI::~CCurSaveUI()
{
}
