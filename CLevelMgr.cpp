#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel_Start.h"
#include "CLevel_Editor.h"
#include "CLevel_Level_01.h"

#include "CEngine.h"

CLevelMgr::CLevelMgr()
	: m_ArrLevel{}
	, m_CurLevelType(LEVEL_TYPE::LEVEL_01)
{
	m_ArrLevel[(UINT)LEVEL_TYPE::START] = new CLevel_Start;
	m_ArrLevel[(UINT)LEVEL_TYPE::EDITOR] = new CLevel_Editor;
	m_ArrLevel[(UINT)LEVEL_TYPE::LEVEL_01] = new CLevel_Level_01;
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
	m_ArrLevel[(UINT)m_CurLevelType]->Tick();
}

void CLevelMgr::FinalTick()
{
	m_ArrLevel[(UINT)m_CurLevelType]->FinalTick();
}

void CLevelMgr::Render()
{
	m_ArrLevel[(UINT)m_CurLevelType]->Render(BackDC);
}

void CLevelMgr::ChangeLevel(LEVEL_TYPE _Type)
{
	m_ArrLevel[(UINT)m_CurLevelType]->Exit();
	m_CurLevelType = _Type;
	m_ArrLevel[(UINT)m_CurLevelType]->Enter();
}

void CLevelMgr::Init()
{
	m_ArrLevel[(UINT)m_CurLevelType]->Enter();
}
