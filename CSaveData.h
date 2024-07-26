#pragma once
#include "CBase.h"

extern array<vector<LEVEL_TYPE>, LEVEL_COUNT + 3> LEVEL_MAP;

class CSaveData
	: public CBase
{
private:
	float           m_PlayTime;

	// �� �������� ���� ���� ���θ� ������. �������� ���� �����ϴ� ������� vector index��
	// vector<bool>�� ������� �������� char Ÿ������ ����
	int             m_StrawberryCnt; // ������ ������ ��
	array<vector<char>, (int)LEVEL_TYPE::END>  m_StrawberryTable;

	// �� �������� ���� ���� ������
	int             m_DeathCount;
	array<int, (int)LEVEL_TYPE::END>	m_DeathTable;

public:
	int GetStrawberryCnt() { return m_StrawberryCnt; }
	int GetDeathCount() { return m_DeathCount; }

	float GetPlayTime() { return m_PlayTime; }

	const vector<char>& GetStrawberryTable(LEVEL_TYPE _Type) { return m_StrawberryTable[(int)_Type]; }
	const vector<char>& GetStrawberryTable(int _Idx) { return m_StrawberryTable[_Idx]; }

	int GetDeathLevel(LEVEL_TYPE _Type) { return m_DeathTable[(int)_Type]; }
	int GetDeathLevel(int _Idx) { return m_DeathTable[_Idx]; }



public:
	void Save(const wstring& _strFileName);
	void Load(const wstring& _strFileName);

public:
	CLONE_DISABLE(CSaveData)
	CSaveData();
	~CSaveData();
	friend class CGameMgr;
};

