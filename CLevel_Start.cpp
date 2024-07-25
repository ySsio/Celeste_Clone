#include "pch.h"
#include "CLevel_Start.h"

#include "CPanelUI.h"
#include "CButtonUI.h"
#include "CAnimUI.h"
#include "CImageUI.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CEngine.h"
#include "CKeyMgr.h"

#include "CSound.h"

CLevel_Start::CLevel_Start()
	: m_BtnIdx(0)
	, m_UIMode(0)
{
}

CLevel_Start::~CLevel_Start()
{
}


void CLevel_Start::Enter()
{
	// ���� �ʱ�ȭ
	m_BtnIdx = 0;
	for (int i = 0; i < 2; ++i)
	{
		m_Btns[i].clear();
	}

	Vec2 vRes = CEngine::Get()->GetResolution();

	CPanelUI* pPanel = new CPanelUI;
	pPanel->SetPos(Vec2(0.f,0.f));
	pPanel->SetScale(vRes);
	pPanel->SetMovable(false);
	pPanel->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\BackGround.png")->Stretch(vRes));
	pPanel->SetTexOffset(vRes/2.f);
	pPanel->SetFix(true);
	AddObject(pPanel, LAYER_TYPE::UI);

	HFONT hFont = CreateFont(
		48,                        // ����
		0,                         // ��
		0,                         // ���� ����
		0,                         // ���̽����� ����
		FW_BOLD,                   // ����
		FALSE,                     // ���Ÿ�ü
		FALSE,                     // ����
		FALSE,                     // ��Ҽ�
		DEFAULT_CHARSET,           // ���ڼ�
		OUT_DEFAULT_PRECIS,        // ��� ���е�
		CLIP_DEFAULT_PRECIS,       // Ŭ���� ���е�
		DEFAULT_QUALITY,           // ��� ǰ��
		DEFAULT_PITCH | FF_SWISS,  // �۲� ���� �� ��ġ
		L"�������"                   // �۲� �̸�
	);

	// ��Ʈ ����
	HFONT hOldFont = (HFONT)SelectObject(BackDC, hFont);

	SetBkMode(BackDC, TRANSPARENT);

	CButtonUI* pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(MAIN_UI_START_BTN_POP_POS_X, 350.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\start.png"));
	pBtn->SetTexOffset(Vec2(80.f, -130.f));
	pBtn->SetFontSize(60);
	pBtn->SetName(L"������");
	pBtn->SetFix(true);

	pPanel->AddChild(pBtn);
	m_Btns[0].push_back(pBtn);

	pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(MAIN_UI_BTN_ORI_POS_X, 480.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\options.png")->Scale(0.5f));
	pBtn->SetTexOffset(Vec2(-50.f, 20.f));
	pBtn->SetFontSize(48);
	pBtn->SetName(L"����");
	pBtn->SetFix(true);

	pPanel->AddChild(pBtn);
	m_Btns[0].push_back(pBtn);

	pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(MAIN_UI_BTN_ORI_POS_X, 580.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\credits.png")->Scale(0.4f));
	pBtn->SetTexOffset(Vec2(-50.f, 20.f));
	pBtn->SetFontSize(48);
	pBtn->SetFix(true);
	pBtn->SetName(L"������");

	pPanel->AddChild(pBtn);
	m_Btns[0].push_back(pBtn);

	pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(MAIN_UI_BTN_ORI_POS_X, 680.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\exit.png")->Scale(0.5f));
	pBtn->SetTexOffset(Vec2(-50.f, 20.f));
	pBtn->SetFontSize(48);
	pBtn->SetFix(true);
	pBtn->SetName(L"����");

	pPanel->AddChild(pBtn);
	m_Btns[0].push_back(pBtn);


	// ���̺� ������ UI
	pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(MAIN_UI_BTN_ORI_POS_X, 680.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\exit.png")->Scale(0.5f));
	pBtn->SetTexOffset(Vec2(-50.f, 20.f));
	pBtn->SetFontSize(48);
	pBtn->SetFix(true);
	pBtn->SetName(L"����");

	pPanel->AddChild(pBtn);
	m_Btns[1].push_back(pBtn);


	// ���� ��Ʈ�� ����
	SelectObject(BackDC, hOldFont);

	// ��Ʈ ����
	DeleteObject(hFont);
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

			m_Btns[(int)m_UIMode][m_BtnIdx]->SetPos(Vec2(MAIN_UI_BTN_ORI_POS_X, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));
			--m_BtnIdx;

			if (m_BtnIdx != 0)
				m_Btns[m_UIMode][m_BtnIdx]->SetPos(Vec2(MAIN_UI_BTN_POP_POS_X, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));
			else
				m_Btns[m_UIMode][m_BtnIdx]->SetPos(Vec2(MAIN_UI_START_BTN_POP_POS_X, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));
		}
	}
	if (KEY_TAP(KEY::DOWN))
	{
		if (m_BtnIdx < m_Btns.size()-1)
		{
			// Sound ���
			CSound* pSound = CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\ui\\ui_main_button_climb.wav");
			pSound->Play();

			if (m_BtnIdx != 0)
				m_Btns[m_UIMode][m_BtnIdx]->SetPos(Vec2(MAIN_UI_BTN_ORI_POS_X, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));
			else
				m_Btns[m_UIMode][m_BtnIdx]->SetPos(Vec2(MAIN_UI_START_BTN_ORI_POS_X, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));

			++m_BtnIdx;
			m_Btns[m_UIMode][m_BtnIdx]->SetPos(Vec2(MAIN_UI_BTN_POP_POS_X, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));
		}
	}


	if (KEY_TAP(KEY::C))
	{
		switch (m_BtnIdx)
		{
		case 0:
			ChangeLevel(LEVEL_TYPE::LEVEL_01);
			break;
			
		case 1:
			ChangeLevel(LEVEL_TYPE::EDITOR);
			break;

		case 2:
			break;

		case 3:
			PostQuitMessage(0);
			break;

		default:
			break;
		}
	}
}

void CLevel_Start::Render_Derived()
{
}
