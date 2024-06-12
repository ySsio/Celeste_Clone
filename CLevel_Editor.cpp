#include "pch.h"
#include "CLevel_Editor.h"
#include "CEngine.h"

#include "resource.h"

#include "CPathMgr.h"

#include "CAnimation.h"
#include "CAssetMgr.h"

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
}
