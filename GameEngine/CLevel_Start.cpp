#include "pch.h"
#include "CLevel_Start.h"

#include "CPanelUI.h"
#include "CButtonUI.h"
#include "CAnimUI.h"
#include "CImageUI.h"
#include "CTextUI.h"
#include "CSaveUI.h"
#include "CCurSaveUI.h"

#include "CEngine.h"
#include "CAssetMgr.h"
#include "CKeyMgr.h"
#include "CGameMgr.h"

#include "CTexture.h"
#include "CSound.h"

CLevel_Start::CLevel_Start()
	: m_BtnIdx(0)
	, m_UIMode(0)
	, m_PanelUI(nullptr)
{
}

CLevel_Start::~CLevel_Start()
{
}


void CLevel_Start::ChangeMode(int _Mode)
{
	DeselectBtn(m_BtnIdx);

	m_UIMode = _Mode;

	Vec2 vRes = CEngine::Get()->GetResolution();

	// 패널을 알맞은 위치로 옮김
	m_PanelUI->MoveSmooth(0.3f, Vec2(-vRes.x * _Mode, 0.f));

	SelectBtn(0);
}

void CLevel_Start::SelectBtn(int _Idx)
{
	Vec2 vRes = CEngine::Get()->GetResolution();
	m_BtnIdx = _Idx;

	switch (m_UIMode)
	{
	case 0:
	{
		if (m_BtnIdx != 0)
			m_Btns[m_UIMode][m_BtnIdx]->MoveSmooth(0.1f, Vec2(MAIN_UI_BTN_POP_POS_X, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));
		else
			m_Btns[m_UIMode][m_BtnIdx]->MoveSmooth(0.1f, Vec2(MAIN_UI_START_BTN_POP_POS_X, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));
	}
	break;

	case 1:
	{
		// 본체 (티켓) 부분은 우측으로 이동
		m_Btns[m_UIMode][m_BtnIdx]->MoveSmooth(0.1f, Vec2(vRes.x * 3.f/2.f + SAVE_UI_BTN_POP_POS_X, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));
		
		// 카드 부분은 좌측으로 이동 (본체의 가장 마지막 자식)
		const auto& vChild = m_Btns[m_UIMode][m_BtnIdx]->GetChild();
		vChild[vChild.size()-1]->MoveSmooth(0.1f, Vec2(-SAVE_UI_BTN_POP_POS_X * 2.f, 0.f));
	}
	break;
	}
}

void CLevel_Start::DeselectBtn(int _Idx)
{
	Vec2 vRes = CEngine::Get()->GetResolution();
	switch (m_UIMode)
	{
	case 0:
	{
		if (m_BtnIdx != 0)
			m_Btns[m_UIMode][m_BtnIdx]->MoveSmooth(0.1f, Vec2(MAIN_UI_BTN_ORI_POS_X, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));
		else
			m_Btns[m_UIMode][m_BtnIdx]->MoveSmooth(0.1f, Vec2(MAIN_UI_START_BTN_ORI_POS_X, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));
	}
	break;

	case 1 :
	{
		// 본체 (티켓) 부분 중앙 정렬
		m_Btns[m_UIMode][m_BtnIdx]->MoveSmooth(0.1f, Vec2(vRes.x * 3.f / 2.f, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));

		// 카드 부분 중앙 정렬
		const auto& vChild = m_Btns[m_UIMode][m_BtnIdx]->GetChild();
		vChild[vChild.size() - 1]->MoveSmooth(0.1f, Vec2(0.f, 0.f));
	}
	break;
	}
}

void CLevel_Start::Enter()
{
	// 변수 초기화
	m_BtnIdx = 0;
	m_UIMode = 0;
	m_PanelUI = nullptr;
	for (int i = 0; i < 2; ++i)
	{
		m_Btns[i].clear();
	}

	// 텍스트 배경 제거
	SetBkMode(BackDC, TRANSPARENT);

	Vec2 vRes = CEngine::Get()->GetResolution();

	m_PanelUI = new CPanelUI;
	m_PanelUI->SetPos(Vec2(0.f,0.f));
	m_PanelUI->SetScale(Vec2(vRes.x * 2.f, vRes.y));
	m_PanelUI->SetMovable(false);
	m_PanelUI->SetFix(true);
	AddObject(m_PanelUI, LAYER_TYPE::UI);

	CImageUI* pImage = new CImageUI;
	pImage->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\BackGround.png")->Stretch(vRes));
	pImage->SetTexOffset(vRes / 2.f);
	pImage->SetFix(true);

	m_PanelUI->AddChild(pImage);

	

	CButtonUI* pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(MAIN_UI_START_BTN_POP_POS_X, 350.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\start.png"));
	pBtn->SetTexOffset(Vec2(80.f, -130.f));
	pBtn->SetFont(L"나눔고딕", 60);
	pBtn->SetName(L"오르기");
	pBtn->SetFunction([=]() { ChangeMode(1); });

	m_PanelUI->AddChild(pBtn);
	m_Btns[0].push_back(pBtn);

	pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(MAIN_UI_BTN_ORI_POS_X, 480.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\options.png")->Scale(0.5f));
	pBtn->SetTexOffset(Vec2(-50.f, 20.f));
	pBtn->SetFont(L"나눔고딕", 48);
	pBtn->SetName(L"편집");
	pBtn->SetFunction([=]() {Change_Level(LEVEL_TYPE::EDITOR); });

	m_PanelUI->AddChild(pBtn);
	m_Btns[0].push_back(pBtn);

	pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(MAIN_UI_BTN_ORI_POS_X, 580.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\credits.png")->Scale(0.4f));
	pBtn->SetTexOffset(Vec2(-50.f, 20.f));
	pBtn->SetFont(L"나눔고딕", 48);
	pBtn->SetName(L"제작진");

	m_PanelUI->AddChild(pBtn);
	m_Btns[0].push_back(pBtn);

	pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(MAIN_UI_BTN_ORI_POS_X, 680.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\exit.png")->Scale(0.5f));
	pBtn->SetTexOffset(Vec2(-50.f, 20.f));
	pBtn->SetFont(L"나눔고딕", 48);
	pBtn->SetName(L"종료");
	pBtn->SetFunction([=]() { PostQuitMessage(0); });
	

	m_PanelUI->AddChild(pBtn);
	m_Btns[0].push_back(pBtn);


	// 세이브 데이터 UI
	const auto& Saves = CGameMgr::Get()->GetSaves();

	for (int i = 0; i < Saves.size(); ++i)
	{
		CCurSaveUI* pSave = new CCurSaveUI(Saves[i]);
		pSave->SetPos(Vec2(vRes.x * 3.f / 2.f, 150.f + 300.f * i));
		m_PanelUI->AddChild(pSave);
		m_Btns[1].push_back(pSave);
	}

	for (int j = Saves.size(); j < 3; ++j)
	{
		CSaveUI* pSave = new CSaveUI;
		pSave->SetPos(Vec2(vRes.x * 3.f / 2.f, 150.f + 300.f * j));
		m_PanelUI->AddChild(pSave);
		m_Btns[1].push_back(pSave);
	}
}

void CLevel_Start::Tick_Derived()
{
	if (KEY_TAP(KEY::UP))
	{
		if (m_BtnIdx > 0)
		{
			// Sound 재생
			if (m_UIMode == 0)
				CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\ui\\ui_main_button_climb.wav")->Play();
			else
				CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\ui\\ui_main_savefile_roll_02.wav")->Play();

			DeselectBtn(m_BtnIdx);
			SelectBtn(m_BtnIdx - 1);
		}
	}
	if (KEY_TAP(KEY::DOWN))
	{
		if (m_BtnIdx < m_Btns[m_UIMode].size() - 1)
		{
			// Sound 재생
			if (m_UIMode == 0)
				CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\ui\\ui_main_button_climb.wav")->Play();
			else
				CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\ui\\ui_main_savefile_roll_02.wav")->Play();

			DeselectBtn(m_BtnIdx);
			SelectBtn(m_BtnIdx + 1);
		}
	}

	
	// C키를 누르면 버튼이 가진 기능을 실행함
	if (KEY_TAP(KEY::C))
	{
		function<void(void)> pFunc = m_Btns[m_UIMode][m_BtnIdx]->GetFunction();

		CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\ui\\ui_main_button_select.wav")->Play();

		if (pFunc)
			pFunc();		
	}

	if (KEY_TAP(KEY::X))
	{
		if (m_UIMode > 0)
			ChangeMode(m_UIMode - 1);
	}
}

void CLevel_Start::Render_Derived()
{
}
