#include "pch.h"
#include "CGamePauseUI.h"

#include "CEngine.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CAssetMgr.h"
#include "CLevelMgr.h"
#include "CGameMgr.h"

#include "CPlayer.h"

#include "CTextUI.h"

CGamePauseUI::CGamePauseUI()
	: m_Activate(false)
	, m_BtnIdx(0)
{
	SetRoom(-2);

	SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\black.png"));

	CTextUI* pText = new CTextUI;
	pText->SetFont(L"나눔고딕", 60);
	pText->SetText(L"일시 중지됨");
	pText->SetColor(RGB(60, 60, 60));
	pText->SetPos(Vec2(-pText->GetScale().x/2.f, -250.f));
	AddChild(pText);

	pText = new CTextUI;
	pText->SetFont(L"나눔고딕", 30);
	pText->SetText(L"계속하기");
	pText->SetColor(RGB(255, 255, 255));
	pText->SetPos(Vec2(-pText->GetScale().x / 2.f, -150.f));
	m_Btns.push_back(pText);
	AddChild(pText);

	pText = new CTextUI;
	pText->SetFont(L"나눔고딕", 30);
	pText->SetText(L"다시시도");
	pText->SetColor(RGB(255, 255, 255));
	pText->SetPos(Vec2(-pText->GetScale().x / 2.f, -100.f));
	m_Btns.push_back(pText);
	AddChild(pText);

	pText = new CTextUI;
	pText->SetFont(L"나눔고딕", 30);
	pText->SetText(L"저장하고 종료하기");
	pText->SetColor(RGB(255, 255, 255));
	pText->SetPos(Vec2(-pText->GetScale().x / 2.f, -50.f));
	m_Btns.push_back(pText);
	AddChild(pText);

	pText = new CTextUI;
	pText->SetFont(L"나눔고딕", 30);
	pText->SetText(L"챕터 다시 시작");
	pText->SetColor(RGB(255, 255, 255));
	pText->SetPos(Vec2(-pText->GetScale().x / 2.f, 20.f));
	m_Btns.push_back(pText);
	AddChild(pText);

	pText = new CTextUI;
	pText->SetFont(L"나눔고딕", 30);
	pText->SetText(L"맵으로 돌아가기");
	pText->SetColor(RGB(255, 255, 255));
	pText->SetPos(Vec2(-pText->GetScale().x / 2.f, 70.f));
	m_Btns.push_back(pText);
	AddChild(pText);
}

CGamePauseUI::~CGamePauseUI()
{
}

void CGamePauseUI::Tick_DerivedUI()
{
	if (KEY_TAP(KEY::ESC))
	{
		m_Activate = !m_Activate;

		if (m_Activate)
		{
			SetRoom(-1);
			m_BtnIdx = 0;
		}
		else
		{
			SetRoom(-2);
		}
	}

	if (m_Activate)
	{
		// 게임 정지
		Pause_Game();

		// BGM 소리 줄임
		if (CGameMgr::Get()->GetBGM())
			CGameMgr::Get()->GetBGM()->SetVolume(20);

		if (KEY_TAP(KEY::DOWN) && m_BtnIdx <= m_Btns.size() - 1)
		{
			// 이전에 활성화된 텍스트는 다시 흰색 으로 표시
			m_Btns[m_BtnIdx]->SetColor(RGB(255, 255, 255));

			if (m_BtnIdx == m_Btns.size()-1)
				m_BtnIdx = 0;
			else
				++m_BtnIdx;
		}

		if (KEY_TAP(KEY::UP) && m_BtnIdx >= 0)
		{
			// 이전에 활성화된 텍스트는 다시 흰색으로 표시
			m_Btns[m_BtnIdx]->SetColor(RGB(255, 255, 255));

			if (m_BtnIdx == 0)
				m_BtnIdx = m_Btns.size() - 1;
			else
				--m_BtnIdx;
		}

		// 현재 활성화된 텍스트는 노란색으로 표시
		m_Btns[m_BtnIdx]->SetColor(RGB(255, 255, 0));

		if (KEY_TAP(KEY::C))
		{
			switch (m_BtnIdx)
			{
			case 0:
			{
				m_Activate = !m_Activate;
				SetRoom(-2);
				m_BtnIdx = 0;				
			}
			break;
			case 1:
			{
				m_Activate = !m_Activate;
				SetRoom(-2);
				m_BtnIdx = 0;

				CGameMgr::Get()->GetPlayer()->GetComponent<CStateMachine>()->ChangeState(L"Dead");
			}
			break;
			case 2:
			{
				PostQuitMessage(0);
			}
			break;
			case 3:
			{
				Release_Game();
				Change_Level(CLevelMgr::Get()->GetCurLevelType());
			}
			break;
			case 4:
			{
				Release_Game();
				Change_Level(LEVEL_TYPE::SELECT);
			}
			break;
			}
		}
	}
	else
	{
		// BGM 소리 키움
		if (CGameMgr::Get()->GetBGM())
			CGameMgr::Get()->GetBGM()->SetVolume(60);

		// 게임 재개
		Release_Game();

		for (auto btn : m_Btns)
		{
			btn->SetColor(RGB(255, 255, 255));
		}
	}
}