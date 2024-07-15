#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel_Start.h"
#include "CLevel_Editor.h"
#include "CLevel_Level_01.h"
#include "CLevel_Level_00.h"

#include "CEngine.h"
#include "CLevel_AnimEditor.h"
#include "CLevel_MapEditor.h"

CLevelMgr::CLevelMgr()
	: m_ArrLevel{}
	, m_CurLevel(nullptr)
{
	m_ArrLevel[(UINT)LEVEL_TYPE::START]			= new CLevel_Start;
	m_ArrLevel[(UINT)LEVEL_TYPE::EDITOR]		= new CLevel_Editor;
	m_ArrLevel[(UINT)LEVEL_TYPE::EDITOR_ANIM]	= new CLevel_AnimEditor;
	m_ArrLevel[(UINT)LEVEL_TYPE::EDITOR_MAP]	= new CLevel_MapEditor;
	m_ArrLevel[(UINT)LEVEL_TYPE::LEVEL_00]		= new CLevel_Level_00;
	m_ArrLevel[(UINT)LEVEL_TYPE::LEVEL_01]		= new CLevel_Level_01;


	m_ArrLevel[(UINT)LEVEL_TYPE::START]->SetName(L"Level_Start");
	m_ArrLevel[(UINT)LEVEL_TYPE::EDITOR]->SetName(L"Level_Editor");
	m_ArrLevel[(UINT)LEVEL_TYPE::EDITOR_ANIM]->SetName(L"Level_AnimEditor");
	m_ArrLevel[(UINT)LEVEL_TYPE::EDITOR_MAP]->SetName(L"Level_MapEditor");
	m_ArrLevel[(UINT)LEVEL_TYPE::LEVEL_01]->SetName(L"Level_01");


	m_CurLevel = m_ArrLevel[(UINT)LEVEL_TYPE::START];
}

CLevelMgr::~CLevelMgr()
{
	for (auto Level : m_ArrLevel)
	{
		delete Level;
	}
}

void CLevelMgr::Tick()
{
	m_CurLevel->Tick();
}

void CLevelMgr::FinalTick()
{
	m_CurLevel->FinalTick();
}

void CLevelMgr::Render()
{
	m_CurLevel->Render();
}

void CLevelMgr::ChangeLevel(LEVEL_TYPE _Type)
{
	if (m_CurLevel)
		m_CurLevel->Exit();

	m_CurLevel = m_ArrLevel[(UINT)_Type];
	m_CurLevel->Enter();
}

void CLevelMgr::Init()
{
	m_CurLevel->Enter();
}
