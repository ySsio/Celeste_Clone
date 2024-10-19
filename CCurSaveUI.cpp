#include "pch.h"
#include "CCurSaveUI.h"

#include "CEngine.h"
#include "CAssetMgr.h"
#include "CGameMgr.h"
#include "CLevelMgr.h"

#include "CImageUI.h"
#include "CAnimUI.h"
#include "CTextUI.h"

#include "CSaveData.h"

CCurSaveUI::CCurSaveUI(CSaveData* _SaveData)
	: m_SaveData(_SaveData)
{
	// 기능 : 게임매니저에서 현재 세이브 데이터를 설정함
	SetFunction([=]() {
		CGameMgr::Get()->SetCurSave(_SaveData); 
		Change_Level(LEVEL_TYPE::SELECT);
	});

	// 티켓 부분 (본체)
	SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\FileSelect\\ticket.png")->Scale(0.9f));

	for (int i = 0; i <= LEVEL_COUNT; ++i)
	{
		CImageUI* pCollect = new CImageUI;
		pCollect->SetPos(Vec2(65.f * i - 210.f, -20.f));
		pCollect->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\FileSelect\\dot.png"));

		AddChild(pCollect);
	}

	CImageUI* pDeath = new CImageUI;
	pDeath->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\collectables\\skullBlue.png"));
	pDeath->SetPos(Vec2(-220.f, 50.f));
	AddChild(pDeath);

	CTextUI* pTextUI = new CTextUI;
	pTextUI->SetPos(Vec2(-180.f, 30.f));
	wstring dtCnt = L"x " + std::to_wstring(m_SaveData->GetDeathCount());
	pTextUI->SetFont(L"나눔고딕", 40);
	pTextUI->SetText(dtCnt.c_str());
	AddChild(pTextUI);

	pTextUI = new CTextUI;
	pTextUI->SetPos(Vec2(120.f, 40.f));
	float PlayTime = m_SaveData->GetPlayTime();
	int min = floor(PlayTime) / 60;
	int hour = min / 60;
	min = min % 60;
	float sec = PlayTime - 60 * 60 * hour - 60 * min;
	wchar_t buffer[100]{};
	swprintf_s(buffer, 100, L"%06.3f", sec);
	wstring strSec = buffer;
	swprintf_s(buffer, 100, L"%02d", hour);
	wstring strHour = buffer;
	swprintf_s(buffer, 100, L"%02d", min);
	wstring strMin = buffer;

	wstring strTime = strHour + L":" + strMin + L":" + strSec;
	pTextUI->SetFont(L"나눔고딕", 30);
	pTextUI->SetText(strTime.c_str());
	AddChild(pTextUI);

	// 카드 부분
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
	pImage->SetPos(Vec2(60.f, 50.f));
	pImage->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\collectables\\strawberry.png")->Scale(0.8f));
	pCard->AddChild(pImage);

	pTextUI = new CTextUI;
	pTextUI->SetPos(Vec2(50.f, -80.f));
	pTextUI->SetFont(L"나눔고딕", 40);
	pTextUI->SetText(L"매들린");
	pCard->AddChild(pTextUI);

	pTextUI = new CTextUI;
	pTextUI->SetPos(Vec2(70.f, -30.f));
	pTextUI->SetFont(L"나눔고딕", 30);
	pTextUI->SetText(L"코어");
	pCard->AddChild(pTextUI);

	pTextUI = new CTextUI;
	pTextUI->SetPos(Vec2(100.f, 35.f));
	wstring stCnt = L"x " + std::to_wstring(m_SaveData->GetStrawberryCnt());
	pTextUI->SetFont(L"나눔고딕", 40);
	pTextUI->SetText(stCnt.c_str());
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
