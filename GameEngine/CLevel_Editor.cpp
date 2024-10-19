#include "pch.h"
#include "CLevel_Editor.h"
#include "CEngine.h"

#include "resource.h"

#include "CPathMgr.h"

#include "CAnimation.h"
#include "CAssetMgr.h"
#include "CLevelMgr.h"

#include "CUI.h"
#include "CPanelUI.h"
#include "CButtonUI.h"

#include "CKeyMgr.h"

CLevel_Editor::CLevel_Editor()
	: m_Menu(nullptr)
{
	m_Menu = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_GAMEENGINE));
}

CLevel_Editor::~CLevel_Editor()
{
	DestroyMenu(m_Menu);
}

void CLevel_Editor::Enter()
{
	SetMenu(CEngine::Get()->GetMainHwnd(), m_Menu);
	CEngine::Get()->ChangeWindowResolution();

	CPanelUI* pPanel = new CPanelUI;
	pPanel->SetPos(Vec2(100.f, 100.f));
	pPanel->SetScale(Vec2(800.f, 600.f));

	AddObject(pPanel, LAYER_TYPE::UI);

	CButtonUI* pButton = new CButtonUI;
	pButton->SetPos(Vec2(100.f, 100.f));
	pButton->SetScale(Vec2(200.f, 100.f));
	pButton->SetName(L"애니메이션 편집");
	pButton->SetFunction([]() {Change_Level(LEVEL_TYPE::EDITOR_ANIM); });

	pPanel->AddChild(pButton);

	pButton = new CButtonUI;
	pButton->SetPos(Vec2(500.f, 100.f));
	pButton->SetScale(Vec2(200.f, 100.f));
	pButton->SetName(L"맵 편집");
	pButton->SetFunction([]() {Change_Level(LEVEL_TYPE::EDITOR_MAP); });

	pPanel->AddChild(pButton);
}

void CLevel_Editor::Tick_Derived()
{
	if (KEY_TAP(KEY::ESC))
	{
		Change_Level(LEVEL_TYPE::START);
	}
}
