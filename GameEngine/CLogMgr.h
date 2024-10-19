#pragma once
#include "CManager.h"
class CLogMgr :
    public CManager
{
	SINGLE(CLogMgr)

private:
	list<tLog>	m_LogList;
	float		m_LogMaxLife;	// �� �α��� lifetime
	UINT		m_LogStep;		// �α� ���� ���� ����

public:
	virtual void Init() override {}
	void SetLogMaxLife(float _Life) { m_LogMaxLife = _Life; }
	void AddLog(const tLog& _Log) { m_LogList.push_front(_Log); }

public:
	void Tick();
};