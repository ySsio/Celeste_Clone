#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel_Start.h"
#include "CLevel_Editor.h"
#include "CLevel_Select.h"
#include "CLevel_00.h"
#include "CLevel_01.h"

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
	m_ArrLevel[(UINT)LEVEL_TYPE::SELECT]		= new CLevel_Select;
	m_ArrLevel[(UINT)LEVEL_TYPE::PROLOGUE]		= new CLevel_00;
	m_ArrLevel[(UINT)LEVEL_TYPE::LEVEL_01_01]	= new CLevel_01_01;


	m_ArrLevel[(UINT)LEVEL_TYPE::START]->SetName(L"Level_Start");
	m_ArrLevel[(UINT)LEVEL_TYPE::EDITOR]->SetName(L"Level_Editor");
	m_ArrLevel[(UINT)LEVEL_TYPE::EDITOR_ANIM]->SetName(L"Level_AnimEditor");
	m_ArrLevel[(UINT)LEVEL_TYPE::EDITOR_MAP]->SetName(L"Level_MapEditor");
	m_ArrLevel[(UINT)LEVEL_TYPE::SELECT]->SetName(L"Level_Select");
	m_ArrLevel[(UINT)LEVEL_TYPE::PROLOGUE]->SetName(L"Level_Prologue");
	m_ArrLevel[(UINT)LEVEL_TYPE::LEVEL_01_01]->SetName(L"Level_01_01");


	m_ArrLevel[(UINT)LEVEL_TYPE::START]->SetLevelType(LEVEL_TYPE::START);
	m_ArrLevel[(UINT)LEVEL_TYPE::EDITOR]->SetLevelType(LEVEL_TYPE::EDITOR);
	m_ArrLevel[(UINT)LEVEL_TYPE::EDITOR_ANIM]->SetLevelType(LEVEL_TYPE::EDITOR_ANIM);
	m_ArrLevel[(UINT)LEVEL_TYPE::EDITOR_MAP]->SetLevelType(LEVEL_TYPE::EDITOR_MAP);
	m_ArrLevel[(UINT)LEVEL_TYPE::SELECT]->SetLevelType(LEVEL_TYPE::SELECT);
	m_ArrLevel[(UINT)LEVEL_TYPE::PROLOGUE]->SetLevelType(LEVEL_TYPE::PROLOGUE);
	m_ArrLevel[(UINT)LEVEL_TYPE::LEVEL_01_01]->SetLevelType(LEVEL_TYPE::LEVEL_01_01);


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
	m_CurLevelType = _Type;
	m_CurLevel->Enter();
}

void CLevelMgr::Init()
{
	m_CurLevel->Enter();
}
