#pragma once
#include "CBase.h"


class CSaveData
	: public CBase
{
private:
	int             m_DeathCount;
	float           m_PlayTime;

	int             m_StrawberryCnt; // ������ ������ ��

	// �� �������� ���� ���� ���θ� ������. �������� ���� �����ϴ� ������� vector index��
	// vector<bool>�� ������� �������� char Ÿ������ ����
	array<vector<char>, (int)LEVEL_TYPE::END>  m_StrawberryTable;

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

