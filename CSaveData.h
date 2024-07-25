#pragma once
#include "CBase.h"

array<vector<LEVEL_TYPE>, LEVEL_COUNT> LEVEL_MAP
{ {
	{LEVEL_TYPE::LEVEL_01_01,LEVEL_TYPE::LEVEL_01_02,LEVEL_TYPE::LEVEL_01_03},
	{LEVEL_TYPE::LEVEL_02_01},
} };

class CSaveData
	: public CBase
{
private:
	float           m_PlayTime;

	// 각 레벨마다 딸기 수집 여부를 저장함. 레벨마다 딸기 생성하는 순서대로 vector index임
	// vector<bool>을 사용하지 않으려고 char 타입으로 저장
	int             m_StrawberryCnt; // 수집한 딸기의 수
	array<vector<char>, (int)LEVEL_TYPE::END>  m_StrawberryTable;

	// 각 레벨마다 데스 수를 저장함
	int             m_DeathCount;
	array<int, (int)LEVEL_TYPE::END>	m_DeathTable;

public:
	int GetStrawberryCnt() { return m_StrawberryCnt; }
	int GetDeathCount() { return m_DeathCount; }

	float GetPlayTime() { return m_PlayTime; }

	const vector<char>& GetStrawberryTable(LEVEL_TYPE _Type) { return m_StrawberryTable[(int)_Type]; }
	const vector<char>& GetStrawberryTable(int _Idx) { return m_StrawberryTable[_Idx]; }

public:
	void Save(const wstring& _strFileName);
	void Load(const wstring& _strFileName);

public:
	CLONE_DISABLE(CSaveData)
	CSaveData();
	~CSaveData();
	friend class CGameMgr;
};

