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
	for (auto& task : m_vecTask)
	{
		switch (task.TaskType)
		{
		case TASK_TYPE::CREATE_OBJECT:
		// wParam : Object Address (CObj*) , lParam : Layer Type (LAYER_TYPE)
		{
			CLevel* pCurLevel = CLevelMgr::Get()->GetCurLevel();
			pCurLevel->AddObject((CObj*)task.wParam, (LAYER_TYPE)task.lParam);
		}
			break;
		case TASK_TYPE::DELETE_OBJECT:
		// wParam : Object Address (CObj*)
		{
			CObj* pObj = (CObj*)task.wParam;

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

			CLevelMgr::Get()->ChangeLevel((LEVEL_TYPE)task.wParam);

			m_LevelChanged = true;
		}
			break;
		default:
			break;
		}
	}
}

void CTaskMgr::Tick()
{
	// dead object 삭제
	for (auto obj : m_GC)
	{
		delete obj;
	}

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
