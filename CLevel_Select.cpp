#include "pch.h"
#include "CLevel_Select.h"

#include "CEngine.h"
#include "CAssetMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CGameMgr.h"

#include "CPanelUI.h"
#include "CImageUI.h"
#include "CButtonUI.h"
#include "CTextUI.h"
#include "CLevelCardUI.h"
#include "CLevelCardUI_Collectable.h"

#include "CSound.h"
#include "CSaveData.h"

CLevel_Select::CLevel_Select()
	: m_BtnIdx(0)
	, m_UIMode(0)
	, m_Panel(nullptr)
	, m_Hover(nullptr)
	, m_Card(nullptr)
	, m_Card_Collectable(nullptr)
{
}

CLevel_Select::~CLevel_Select()
{
}

const float Gap = 180.f;


void CLevel_Select::ChangeMode(int _Mode)
{
	m_UIMode = _Mode;
}

void CLevel_Select::Enter()
{
	// ���� �ʱ�ȭ
	m_Btns.clear();
	m_BtnIdx = 0;
	m_UIMode = 0;
	m_Panel = nullptr;
	m_Hover = nullptr;
	m_Card = nullptr;
	m_Card_Collectable = nullptr;

	Vec2 vRes = CEngine::Get()->GetResolution();

	m_Panel = new CPanelUI;
	m_Panel->SetPos(vRes/2.f);
	m_Panel->SetScale(vRes);
	m_Panel->SetMovable(false);
	m_Panel->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\menu\\BackGround.png")->Stretch(vRes));
	m_Panel->SetFix(true);

	AddObject(m_Panel, LAYER_TYPE::UI);

	// ī�� ����
	// ī�� UI (���� ����)
	m_Card = new CLevelCardUI;
	m_Card->SetPos(Vec2(vRes.x, -360.f));
	m_Panel->AddChild(m_Card);

	m_Card_Collectable = new CLevelCardUI_Collectable;
	m_Card_Collectable->SetPos(Vec2(vRes.x, -360.f));
	m_Panel->AddChild(m_Card_Collectable);
	
	// �� ������ �κ�
	m_Hover = new CImageUI;
	m_Hover->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"\\texture\\Gui\\areas\\hover.png")->Scale(0.9f));
	m_Hover->SetPos(Vec2(0.f, -350.f));
	m_Panel->AddChild(m_Hover);

	vector<wstring> Names{ L"intro", L"city", L"oldsite", L"resort", L"cliffside", L"temple", L"reflection", L"Summit", L"intro", L"core" };

	for (int i = 0; i < Names.size(); ++i)
	{
		CButtonUI* pBtn = new CButtonUI;
		pBtn->SetTex(CAssetMgr::Get()->LoadAsset<CTexture>(L"Icon_"+Names[i], L"\\texture\\Gui\\areas\\" + Names[i] + L".png")->Scale(0.7f));
		pBtn->SetPos(Vec2(Gap * i, -350.f));
		m_Panel->AddChild(pBtn);

		m_Btns.push_back(pBtn);
	}

	
}

void CLevel_Select::Tick_Derived()
{
	if (m_UIMode == 0)
	{
		if (KEY_TAP(KEY::LEFT))
		{
			if (m_BtnIdx > 0 && !m_Btns[0]->IsMoving())
			{
				// Sound ���
				CSound* pSound = CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\ui\\ui_main_button_climb.wav");
				pSound->Play();

				--m_BtnIdx;

				// ��ü �������� �̵�
				for (auto btn : m_Btns)
				{
					btn->SetPosSmooth(0.1f, btn->GetPos() + Vec2(Gap, 0.f));
				}
			}
		}
		if (KEY_TAP(KEY::RIGHT))
		{
			if (m_BtnIdx < m_Btns.size() - 1 && !m_Btns[0]->IsMoving())
			{
				// Sound ���
				CSound* pSound = CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\ui\\ui_main_button_climb.wav");
				pSound->Play();

				++m_BtnIdx;

				// ��ü �������� �̵�
				for (auto btn : m_Btns)
				{
					btn->SetPosSmooth(0.1f, btn->GetPos() - Vec2(Gap, 0.f));
				}
			}
		}
	}

	Vec2 vRes = CEngine::Get()->GetResolution();

	// ���� ��ư ������ ���
	if (KEY_TAP(KEY::C))
	{
		switch (m_UIMode)
		{
		case 0:
		{
			// ��ü ���� �̵�
			m_Hover->SetPosSmooth(0.2f, m_Hover->GetPos() - Vec2(0.f, 1.5f * Gap));
			for (int i=0; i<m_Btns.size(); ++i)
			{
				if (i == m_BtnIdx)
					continue;
				
				m_Btns[i]->SetPosSmooth(0.5f,  Vec2(Gap * (i - m_BtnIdx), -600.f));
			}

			if (1 <= m_BtnIdx && m_BtnIdx <= LEVEL_COUNT)
			{
				// ī�� ���� ������Ʈ
				m_Card_Collectable->SetValueWithLevel(m_BtnIdx);

				// �����ʿ��� ī�� ������
				m_Card_Collectable->SetPosSmooth(0.5f, Vec2(vRes.x / 2.f - m_Card_Collectable->GetScale().x / 2.f, -360.f));
			}
			else
			{
				// ī�� ���� ������Ʈ
				m_Card->SetValueWithLevel(m_BtnIdx);

				// �����ʿ��� ī�� ������
				m_Card->SetPosSmooth(0.5f, Vec2(vRes.x / 2.f - m_Card->GetScale().x / 2.f, -360.f));
			}

			// �������� ī�� ���� �̵�
			m_Btns[m_BtnIdx]->SetPosSmooth(0.5f, Vec2(650.f, -300.f));
			
			// ��� ����
			ChangeMode(1);
		}
		break;

		case 1:
		{
			CLevelMgr::Get()->ChangeLevel(LEVEL_MAP[m_BtnIdx][0]);
		}
		break;
		}
	}

	// ��� ��ư ������ ���
	if (KEY_TAP(KEY::X))
	{
		switch (m_UIMode)
		{
		case 0:
		{
			CLevelMgr::Get()->ChangeLevel(LEVEL_TYPE::START);
		}
		break;

		case 1:
		{
			if (m_Card->IsMoving() || m_Card_Collectable->IsMoving())
				break;

			// ��ü �����ڸ��� �̵�
			m_Hover->SetPosSmooth(0.2f, m_Hover->GetPos() + Vec2(0.f, 1.5f * Gap));
			for (int i = 0; i < m_Btns.size(); ++i)
			{
				m_Btns[i]->SetPosSmooth(0.2f, Vec2(Gap* (i - m_BtnIdx), -350.f));
			}

			// ���������� ī�� ����
			if (1 <= m_BtnIdx && m_BtnIdx <= LEVEL_COUNT)
			{
				m_Card_Collectable->SetPosSmooth(0.15f, Vec2(vRes.x, -360.f));
			}
			else
			{
				m_Card->SetPosSmooth(0.2f, Vec2(vRes.x, -360.f));
			}

			// ��� ����
			ChangeMode(0);
		}
		break;
		}
	}
}