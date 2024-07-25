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
	void Save(const wstring& _strFileName);
	void Load(const wstring& _strFileName);

public:
	CLONE_DISABLE(CSaveData)
	CSaveData();
	~CSaveData();
	friend class CGameMgr;
};

