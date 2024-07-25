#include "pch.h"
#include "CLevel_Start.h"

#include "CPanelUI.h"
#include "CButtonUI.h"
#include "CAnimUI.h"
#include "CImageUI.h"
#include "CTextUI.h"

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
	m_UIMode = _Mode;

	Vec2 vRes = CEngine::Get()->GetResolution();

	// �г��� �˸��� ��ġ�� �ű�
	m_PanelUI->SetPos(Vec2(-vRes.x * _Mode, 0.f));
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
			m_Btns[m_UIMode][m_BtnIdx]->SetPos(Vec2(MAIN_UI_BTN_POP_POS_X, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));
		else
			m_Btns[m_UIMode][m_BtnIdx]->SetPos(Vec2(MAIN_UI_START_BTN_POP_POS_X, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));
	}
	break;

	case 1:
	{
		m_Btns[m_UIMode][m_BtnIdx]->SetPos(Vec2(vRes.x * 3.f/2.f + SAVE_UI_BTN_POP_POS_X, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));
		m_Btns[m_UIMode][m_BtnIdx]->GetChild()[0]->SetPos(Vec2(-SAVE_UI_BTN_POP_POS_X * 2.f, 0.f));
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
			m_Btns[m_UIMode][m_BtnIdx]->SetPos(Vec2(MAIN_UI_BTN_ORI_POS_X, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));
		else
			m_Btns[m_UIMode][m_BtnIdx]->SetPos(Vec2(MAIN_UI_START_BTN_ORI_POS_X, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));
	}
	break;

	case 1 :
	{
		m_Btns[m_UIMode][m_BtnIdx]->SetPos(Vec2(vRes.x * 3.f / 2.f, m_Btns[m_UIMode][m_BtnIdx]->GetPos().y));
		m_Btns[m_UIMode][m_BtnIdx]->GetChild()[0]->SetPos(Vec2(0.f, 0.f));
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

	m_PanelUI->AddChild(pBtn);
	m_Btns[0].push_back(pBtn);

	pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(MAIN_UI_BTN_ORI_POS_X, 480.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\options.png")->Scale(0.5f));
	pBtn->SetTexOffset(Vec2(-50.f, 20.f));
	pBtn->SetFontSize(48);
	pBtn->SetName(L"����");

	m_PanelUI->AddChild(pBtn);
	m_Btns[0].push_back(pBtn);

	pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(MAIN_UI_BTN_ORI_POS_X, 580.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\credits.png")->Scale(0.4f));
	pBtn->SetTexOffset(Vec2(-50.f, 20.f));
	pBtn->SetFontSize(48);
	pBtn->SetName(L"������");

	m_PanelUI->AddChild(pBtn);
	m_Btns[0].push_back(pBtn);

	pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(MAIN_UI_BTN_ORI_POS_X, 680.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\exit.png")->Scale(0.5f));
	pBtn->SetTexOffset(Vec2(-50.f, 20.f));
	pBtn->SetFontSize(48);
	pBtn->SetName(L"����");

	m_PanelUI->AddChild(pBtn);
	m_Btns[0].push_back(pBtn);


	// ���̺� ������ UI
	const auto& Saves = CGameMgr::Get()->GetSaves();

	CButtonUI* pSave = new CButtonUI;
	pSave->SetPos(Vec2(vRes.x * 3.f/2.f, 150.f));
	pSave->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\FileSelect\\ticket.png")->Scale(0.9f));
	m_PanelUI->AddChild(pSave);
	m_Btns[1].push_back(pSave);

	CImageUI* pCard = new CImageUI;
	pCard->SetPos(Vec2(0.f, 0.f));
	pCard->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\FileSelect\\card.png")->Scale(0.9f));
	pCard->SetTexOffset(Vec2(0.f, 0.f));
	pSave->AddChild(pCard);

	CAnimUI* pPortrait = new CAnimUI;
	pPortrait->SetPos(Vec2(-200.f, 0.f));
	pPortrait->SetAnim(L"Madeliene_Portrait", CAssetMgr::Get()->LoadAsset<CAnimation>(L"\\animation\\Portrait.anim"));
	pCard->AddChild(pPortrait);

	pImage = new CImageUI;
	pImage->SetPos(Vec2(-200.f, 0.f));
	pImage->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\FileSelect\\portraitOverlay.png")->Scale(0.9f));
	pCard->AddChild(pImage);

	CTextUI* pTextUI = new CTextUI;
	pTextUI->SetPos(Vec2(50.f, -80.f));
	pTextUI->SetText(L"�ŵ鸰");
	pTextUI->SetFont(L"Arial", 40);
	pCard->AddChild(pTextUI);

	pTextUI = new CTextUI;
	pTextUI->SetPos(Vec2(50.f, -40.f));
	pTextUI->SetText(L"�ھ�");
	pTextUI->SetFont(L"Arial", 30);
	pCard->AddChild(pTextUI);

	pBtn = new CButtonUI{ *pSave };
	pBtn->SetPos(Vec2(vRes.x * 3.f / 2.f, 450.f));
	m_PanelUI->AddChild(pBtn);
	m_Btns[1].push_back(pBtn);

	pBtn = new CButtonUI{ *pSave };
	pBtn->SetPos(Vec2(vRes.x * 3.f / 2.f, 750.f));
	m_PanelUI->AddChild(pBtn);
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

	

	if (KEY_TAP(KEY::C))
	{
		switch (m_UIMode)
		{
		case 0:
		{
			switch (m_BtnIdx)
			{
			case 0:
			{
				Vec2 vRes = CEngine::Get()->GetResolution();
				m_PanelUI->SetPos(Vec2(-vRes.x, 0.f));

				ChangeMode(1);


			}
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
		break;

		case 1 :
		{

		}
		break;

		}
		
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
