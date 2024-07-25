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

	// �г��� �˸��� ��ġ�� �ű�
	m_PanelUI->SetPosSmooth(0.3f, Vec2(-vRes.x * _Mode, 0.f));

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
			m_Btns[m_UIMode][m_BtnIdx]->SetPosSmooth(0.1f, Vec2(MAIN_UI_BTN_POP_POS_X, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));
		else
			m_Btns[m_UIMode][m_BtnIdx]->SetPosSmooth(0.1f, Vec2(MAIN_UI_START_BTN_POP_POS_X, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));
	}
	break;

	case 1:
	{
		// ��ü (Ƽ��) �κ��� �������� �̵�
		m_Btns[m_UIMode][m_BtnIdx]->SetPosSmooth(0.1f, Vec2(vRes.x * 3.f/2.f + SAVE_UI_BTN_POP_POS_X, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));
		
		// ī�� �κ��� �������� �̵� (��ü�� ���� ������ �ڽ�)
		const auto& vChild = m_Btns[m_UIMode][m_BtnIdx]->GetChild();
		vChild[vChild.size()-1]->SetPosSmooth(0.1f, Vec2(-SAVE_UI_BTN_POP_POS_X * 2.f, 0.f));
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
			m_Btns[m_UIMode][m_BtnIdx]->SetPosSmooth(0.1f, Vec2(MAIN_UI_BTN_ORI_POS_X, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));
		else
			m_Btns[m_UIMode][m_BtnIdx]->SetPosSmooth(0.1f, Vec2(MAIN_UI_START_BTN_ORI_POS_X, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));
	}
	break;

	case 1 :
	{
		// ��ü (Ƽ��) �κ� �߾� ����
		m_Btns[m_UIMode][m_BtnIdx]->SetPosSmooth(0.1f, Vec2(vRes.x * 3.f / 2.f, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));

		// ī�� �κ� �߾� ����
		const auto& vChild = m_Btns[m_UIMode][m_BtnIdx]->GetChild();
		vChild[vChild.size() - 1]->SetPosSmooth(0.1f, Vec2(0.f, 0.f));
	}
	break;
	}
}

void CLevel_Start::Enter()
{
	// ���� �ʱ�ȭ
	m_BtnIdx = 0;
	for (int i = 0; i < 2; ++i)
	{
		m_Btns[i].clear();
	}

	// �ؽ�Ʈ ��� ����
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
	pBtn->SetFont(L"�������", 60);
	pBtn->SetName(L"������");
	pBtn->SetFunction([=]() { ChangeMode(1); });

	m_PanelUI->AddChild(pBtn);
	m_Btns[0].push_back(pBtn);

	pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(MAIN_UI_BTN_ORI_POS_X, 480.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\options.png")->Scale(0.5f));
	pBtn->SetTexOffset(Vec2(-50.f, 20.f));
	pBtn->SetFont(L"�������", 48);
	pBtn->SetName(L"����");
	pBtn->SetFunction([=]() {ChangeLevel(LEVEL_TYPE::EDITOR); });

	m_PanelUI->AddChild(pBtn);
	m_Btns[0].push_back(pBtn);

	pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(MAIN_UI_BTN_ORI_POS_X, 580.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\credits.png")->Scale(0.4f));
	pBtn->SetTexOffset(Vec2(-50.f, 20.f));
	pBtn->SetFont(L"�������", 48);
	pBtn->SetName(L"������");

	m_PanelUI->AddChild(pBtn);
	m_Btns[0].push_back(pBtn);

	pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(MAIN_UI_BTN_ORI_POS_X, 680.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\exit.png")->Scale(0.5f));
	pBtn->SetTexOffset(Vec2(-50.f, 20.f));
	pBtn->SetFont(L"�������", 48);
	pBtn->SetName(L"����");
	pBtn->SetFunction([=]() {PostQuitMessage(0); });
	

	m_PanelUI->AddChild(pBtn);
	m_Btns[0].push_back(pBtn);


	// ���̺� ������ UI
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
			// Sound ���
			CSound* pSound = CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\ui\\ui_main_button_climb.wav");
			pSound->Play();

			DeselectBtn(m_BtnIdx);
			SelectBtn(m_BtnIdx - 1);
		}
	}
	if (KEY_TAP(KEY::DOWN))
	{
		if (m_BtnIdx < m_Btns[m_UIMode].size() - 1)
		{
			// Sound ���
			CSound* pSound = CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\ui\\ui_main_button_climb.wav");
			pSound->Play();

			DeselectBtn(m_BtnIdx);
			SelectBtn(m_BtnIdx + 1);
		}
	}

	
	// CŰ�� ������ ��ư�� ���� ����� ������
	if (KEY_TAP(KEY::C))
	{
		function<void(void)> pFunc = m_Btns[m_UIMode][m_BtnIdx]->GetFunction();

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
