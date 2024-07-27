#include "pch.h"
#include "CTaskMgr.h"
#include "CObj.h"
#include "CLevelMgr.h"
#include "CLevel.h"

CTaskMgr::CTaskMgr()
	: m_LevelChanged(false)
{

}

CTaskMgr::~CTaskMgr()
{

}

void CTaskMgr::ExecuteTask(const tTask& _task)
{
	switch (_task.TaskType)
	{
	case TASK_TYPE::CREATE_OBJECT:
	// wParam : Object Address (CObj*) , lParam : Layer Type (LAYER_TYPE)
	{
		CLevel* pCurLevel = CLevelMgr::Get()->GetCurLevel();
		pCurLevel->AddObject((CObj*)_task.wParam, (LAYER_TYPE)_task.lParam);
	}
		break;
	case TASK_TYPE::DELETE_OBJECT:
	// wParam : Object Address (CObj*)
	{
		CObj* pObj = (CObj*)_task.wParam;

		if (pObj->IsDead()) return;

		pObj->SetDead();
		m_GC.push_back(pObj);
	}
		break;
	case TASK_TYPE::CHANGE_LEVEL:
	// wParam : Level Type (LEVEL_TYPE)
	{
		if (m_LevelChanged)
			return;

		CLevelMgr::Get()->ChangeLevel((LEVEL_TYPE)_task.wParam);

		m_LevelChanged = true;
	}
		break;
	case TASK_TYPE::RESET_LEVEL:
	// wParam : Level Type (LEVEL_TYPE)
	{
		CLevelMgr::Get()->GetCurLevel()->Reset();
	}
	break;
	}
}

void CTaskMgr::Tick()
{
	// dead object 삭제
	for (auto obj : m_GC)
	{
		delete obj;
	}
	m_GC.clear();

	// task 처리
	for (const auto& task : m_vecTask)
	{
		ExecuteTask(task);
	}

	m_vecTask.clear();
	m_LevelChanged = false;
}

void CTaskMgr::Init()
{
}
