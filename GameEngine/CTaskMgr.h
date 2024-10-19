#pragma once
#include "CManager.h"

struct tTask
{
	TASK_TYPE	TaskType;
	DWORD_PTR	wParam;			// �ּҰ� ������ �پ��� ���� �����ϱ� ���� 8byte �ڷ������� ����
	DWORD_PTR   lParam;
};

class CTaskMgr :
    public CManager
{
    SINGLE(CTaskMgr)

private:
	vector<tTask>	m_vecTask;

	vector<CObj*>	m_GC; // Garbage Collector

	bool			m_LevelChanged;

public:
	void AddTask(const tTask& _task) { m_vecTask.push_back(_task); }
	void ExecuteTask(const tTask& _task);

public:
	void Tick();
    virtual void Init() override;


public:


};

