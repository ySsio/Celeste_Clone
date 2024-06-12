#include "pch.h"
#include "CLevelMgr.h"

#include "CLevel_Start.h"
#include "CLevel_Editor.h"
#include "CLevel_Level_01.h"

#include "CEngine.h"

CLevelMgr::CLevelMgr()
	: m_ArrLevel{}
	, m_CurLevel(nullptr)
{
	m_ArrLevel[(UINT)LEVEL_TYPE::START] = new CLevel_Start;
	m_ArrLevel[(UINT)LEVEL_TYPE::EDITOR] = new CLevel_Editor;
	m_ArrLevel[(UINT)LEVEL_TYPE::LEVEL_01] = new CLevel_Level_01;


	m_CurLevel = m_ArrLevel[(UINT)LEVEL_TYPE::EDITOR];
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

void CLevelMgr::ChangeLevel(CLevel* _Level)
{
	if (m_CurLevel)
		m_CurLevel->Exit();

	m_CurLevel = _Level;
	_Level->Enter();
}

void CLevelMgr::Init()
{
	m_CurLevel->Enter();
}
