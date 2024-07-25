#pragma once
#include "CBase.h"

class CSaveData
	: public CBase
{
private:
	int             m_DeathCount;
	float           m_PlayTime;

	int             m_StrawberryCnt; // 수집한 딸기의 수

	// 각 레벨마다 딸기 수집 여부를 저장함. 레벨마다 딸기 생성하는 순서대로 vector index임
	// vector<bool>을 사용하지 않으려고 char 타입으로 저장
	array<vector<char>, (int)LEVEL_TYPE::END>  m_StrawberryTable;

public:
	void Save(const wstring& _strFileName);
	void Load(const wstring& _strFileName);

public:
	CLONE_DISABLE(CSaveData)
	CSaveData();
	~CSaveData();
	friend class CGameMgr;
};

