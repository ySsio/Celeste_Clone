#include "pch.h"
#include "CLevel_Start.h"

#include "CPanelUI.h"
#include "CButtonUI.h"
#include "CAssetMgr.h"
#include "CTexture.h"

#include "CEngine.h"
#include "CKeyMgr.h"

CLevel_Start::CLevel_Start()
	: m_BtnIdx(0)
{
}

CLevel_Start::~CLevel_Start()
{
}


void CLevel_Start::Enter()
{
	Vec2 vRes = CEngine::Get()->GetResolution();

	CPanelUI* pPanel = new CPanelUI;
	pPanel->SetPos(Vec2(0.f,0.f));
	pPanel->SetScale(vRes);
	pPanel->SetMovable(false);
	pPanel->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\BackGround.png"));
	pPanel->SetTexOffset(vRes/2.f);
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
	pBtn->SetPos(Vec2(160.f, 350.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\start.png"));
	pBtn->SetTexOffset(Vec2(80.f, -130.f));
	pBtn->SetFontSize(60);
	pBtn->SetName(L"������");

	pPanel->AddChild(pBtn);
	m_Btns.push_back(pBtn);

	pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(200.f, 480.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\options.png")->Scale(0.5f));
	pBtn->SetTexOffset(Vec2(-50.f, 20.f));
	pBtn->SetFontSize(48);
	pBtn->SetName(L"�ɼ�");

	pPanel->AddChild(pBtn);
	m_Btns.push_back(pBtn);

	pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(200.f, 580.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\credits.png")->Scale(0.4f));
	pBtn->SetTexOffset(Vec2(-50.f, 20.f));
	pBtn->SetFontSize(48);
	pBtn->SetName(L"������");

	pPanel->AddChild(pBtn);
	m_Btns.push_back(pBtn);

	pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(200.f, 680.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\exit.png")->Scale(0.5f));
	pBtn->SetTexOffset(Vec2(-50.f, 20.f));
	pBtn->SetFontSize(48);
	pBtn->SetName(L"����");

	pPanel->AddChild(pBtn);
	m_Btns.push_back(pBtn);

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
			m_Btns[m_BtnIdx]->SetPos(Vec2(m_Btns[m_BtnIdx]->GetPos().x - 50.f, m_Btns[m_BtnIdx]->GetPos().y));
			--m_BtnIdx;
			m_Btns[m_BtnIdx]->SetPos(Vec2(m_Btns[m_BtnIdx]->GetPos().x + 50.f, m_Btns[m_BtnIdx]->GetPos().y));
		}
	}
	if (KEY_TAP(KEY::DOWN))
	{
		if (m_BtnIdx < m_Btns.size()-1)
		{
			m_Btns[m_BtnIdx]->SetPos(Vec2(m_Btns[m_BtnIdx]->GetPos().x - 50.f, m_Btns[m_BtnIdx]->GetPos().y));
			++m_BtnIdx;
			m_Btns[m_BtnIdx]->SetPos(Vec2(m_Btns[m_BtnIdx]->GetPos().x + 50.f, m_Btns[m_BtnIdx]->GetPos().y));
		}
	}

	if (KEY_TAP(KEY::C))
	{
		switch (m_BtnIdx)
		{
		case 0:
			break;
			
		case 1:
			break;

		case 2:
			break;

		case 3:
			break;

		default:
			break;
		}
	}
}

void CLevel_Start::Render_Derived()
{
}
