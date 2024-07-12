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
		48,                        // 높이
		0,                         // 폭
		0,                         // 기울기 각도
		0,                         // 베이스라인 각도
		FW_BOLD,                   // 굵기
		FALSE,                     // 이탤릭체
		FALSE,                     // 밑줄
		FALSE,                     // 취소선
		DEFAULT_CHARSET,           // 문자셋
		OUT_DEFAULT_PRECIS,        // 출력 정밀도
		CLIP_DEFAULT_PRECIS,       // 클리핑 정밀도
		DEFAULT_QUALITY,           // 출력 품질
		DEFAULT_PITCH | FF_SWISS,  // 글꼴 가족 및 피치
		L"나눔고딕"                   // 글꼴 이름
	);

	// 폰트 선택
	HFONT hOldFont = (HFONT)SelectObject(BackDC, hFont);

	SetBkMode(BackDC, TRANSPARENT);

	CButtonUI* pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(160.f, 350.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\start.png"));
	pBtn->SetTexOffset(Vec2(80.f, -130.f));
	pBtn->SetFontSize(60);
	pBtn->SetName(L"오르기");

	pPanel->AddChild(pBtn);
	m_Btns.push_back(pBtn);

	pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(200.f, 480.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\options.png")->Scale(0.5f));
	pBtn->SetTexOffset(Vec2(-50.f, 20.f));
	pBtn->SetFontSize(48);
	pBtn->SetName(L"옵션");

	pPanel->AddChild(pBtn);
	m_Btns.push_back(pBtn);

	pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(200.f, 580.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\credits.png")->Scale(0.4f));
	pBtn->SetTexOffset(Vec2(-50.f, 20.f));
	pBtn->SetFontSize(48);
	pBtn->SetName(L"제작진");

	pPanel->AddChild(pBtn);
	m_Btns.push_back(pBtn);

	pBtn = new CButtonUI;
	pBtn->SetPos(Vec2(200.f, 680.f));
	pBtn->SetScale(Vec2(200.f, 70.f));
	pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\exit.png")->Scale(0.5f));
	pBtn->SetTexOffset(Vec2(-50.f, 20.f));
	pBtn->SetFontSize(48);
	pBtn->SetName(L"종료");

	pPanel->AddChild(pBtn);
	m_Btns.push_back(pBtn);

	// 원래 폰트로 복원
	SelectObject(BackDC, hOldFont);

	// 폰트 삭제
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
