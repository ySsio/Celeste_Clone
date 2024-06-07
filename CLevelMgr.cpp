#include "pch.h"
#include "CLevelMgr.h"
#include "CLevel.h"

#include "CLevel_Start.h"
#include "CLevel_Editor.h"
#include "CLevel_Level_01.h"

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

}

void CLevelMgr::Tick()
{
	m_ArrLevel[(UINT)m_CurLevelType]->Tick();
}

void CLevelMgr::Render(HDC _hDC)
{
	m_ArrLevel[(UINT)m_CurLevelType]->Render(_hDC);
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
