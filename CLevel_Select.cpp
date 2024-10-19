#include "pch.h"
#include "CLevel_Select.h"

#include "CEngine.h"
#include "CAssetMgr.h"
#include "CKeyMgr.h"
#include "CLevelMgr.h"
#include "CGameMgr.h"
#include "CTimeMgr.h"
#include "CCamera.h"

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
	m_AccTime = 0.f;
	m_ToGame = false;

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
	if (m_ToGame)
	{
		m_AccTime += fDT;

		if (m_AccTime >= 1.f)
		{
			// ���� ����
			Change_Level(LEVEL_MAP[m_BtnIdx][0]);

			m_AccTime = 0.f;
		}

		return;
	}


	if (m_UIMode == 0)
	{
		if (KEY_TAP(KEY::LEFT))
		{
			if (m_BtnIdx > 0 && !m_Btns[0]->IsMoving())
			{
				// Sound ���
				CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\ui\\ui_world_icon_flip_right.wav")->Play();

				--m_BtnIdx;

				// ��ü �������� �̵�
				for (auto btn : m_Btns)
				{
					btn->MoveSmooth(0.1f, btn->GetPos() + Vec2(Gap, 0.f));
				}
			}
		}
		if (KEY_TAP(KEY::RIGHT))
		{
			if (m_BtnIdx < m_Btns.size() - 1 && !m_Btns[0]->IsMoving())
			{
				// Sound ���
				CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\ui\\ui_world_icon_flip_right.wav")->Play();

				++m_BtnIdx;

				// ��ü �������� �̵�
				for (auto btn : m_Btns)
				{
					btn->MoveSmooth(0.1f, btn->GetPos() - Vec2(Gap, 0.f));
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
			m_Hover->MoveSmooth(0.2f, m_Hover->GetPos() - Vec2(0.f, 1.5f * Gap));
			for (int i=0; i<m_Btns.size(); ++i)
			{
				if (i == m_BtnIdx)
					continue;
				
				m_Btns[i]->MoveSmooth(0.5f,  Vec2(Gap * (i - m_BtnIdx), -600.f));
			}

			if (1 <= m_BtnIdx && m_BtnIdx <= LEVEL_COUNT)
			{
				// ī�� ���� ������Ʈ
				m_Card_Collectable->SetValueWithLevel(m_BtnIdx);

				// �����ʿ��� ī�� ������
				m_Card_Collectable->MoveSmooth(0.5f, Vec2(vRes.x / 2.f - m_Card_Collectable->GetScale().x / 2.f, -360.f));
			}
			else
			{
				// ī�� ���� ������Ʈ
				m_Card->SetValueWithLevel(m_BtnIdx);

				// �����ʿ��� ī�� ������
				m_Card->MoveSmooth(0.5f, Vec2(vRes.x / 2.f - m_Card->GetScale().x / 2.f, -360.f));
			}

			// �������� ī�� ���� �̵�
			m_Btns[m_BtnIdx]->MoveSmooth(0.5f, Vec2(650.f, -300.f));
			
			// ���� ���
			CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\ui\\ui_world_icon_select.wav")->Play();

			// ��� ����
			ChangeMode(1);
		}
		break;

		case 1:
		{
			// ī�޶� ȿ��
			CCamera::Get()->SetCamEffect(CAM_EFFECT::RESPAWN);

			// ���� ���
			CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\ui\\ui_world_chapter_checkpoint_start.wav")->Play();

			// ���� ����
			m_ToGame = true;
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
			Change_Level(LEVEL_TYPE::START);
		}
		break;

		case 1:
		{
			if (m_Card->IsMoving() || m_Card_Collectable->IsMoving())
				break;

			// ��ü �����ڸ��� �̵�
			m_Hover->MoveSmooth(0.2f, m_Hover->GetPos() + Vec2(0.f, 1.5f * Gap));
			for (int i = 0; i < m_Btns.size(); ++i)
			{
				m_Btns[i]->MoveSmooth(0.2f, Vec2(Gap* (i - m_BtnIdx), -350.f));
			}

			// ���������� ī�� ����
			if (1 <= m_BtnIdx && m_BtnIdx <= LEVEL_COUNT)
			{
				m_Card_Collectable->MoveSmooth(0.15f, Vec2(vRes.x, -360.f));
			}
			else
			{
				m_Card->MoveSmooth(0.2f, Vec2(vRes.x, -360.f));
			}

			// ���� ���
			CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\ui\\ui_world_chapter_back.wav")->Play();

			// ��� ����
			ChangeMode(0);
		}
		break;
		}
	}
}