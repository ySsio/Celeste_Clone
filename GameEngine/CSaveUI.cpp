#include "pch.h"
#include "CSaveUI.h"

#include "CEngine.h"
#include "CAssetMgr.h"
#include "CGameMgr.h"
#include "CLevelMgr.h"

#include "CImageUI.h"
#include "CAnimUI.h"
#include "CTextUI.h"


CSaveUI::CSaveUI()
{
	// 기능 : 새 세이브 데이터를 생성
	SetFunction([]() {
		CSaveData* pSave = CGameMgr::Get()->AddNewSaveData();
		CGameMgr::Get()->SetCurSave(pSave);
		Change_Level(LEVEL_TYPE::SELECT);
	});

	SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\FileSelect\\ticket.png")->Scale(0.9f));

	CImageUI* pCard = new CImageUI;
	pCard->SetPos(Vec2(0.f, 0.f));
	pCard->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\FileSelect\\card.png")->Scale(0.9f));
	pCard->SetTexOffset(Vec2(0.f, 0.f));
	AddChild(pCard);
}

CSaveUI::~CSaveUI()
{
}

void CSaveUI::Render_DerivedUI()
{
	GetSprite()->Render();
}