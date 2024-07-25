#include "pch.h"
#include "CSaveData.h"
#include "CPathMgr.h"

CSaveData::CSaveData()
	: m_DeathCount(0)
	, m_PlayTime(0.f)
	, m_StrawberryCnt(0)
{
}

CSaveData::~CSaveData()
{
}


void CSaveData::Save(const wstring& _strFileName)
{
	// �̸� ����
	SetName(_strFileName);

	wstring SavePath = CPathMgr::Get()->GetSavePath();
	SavePath += L"\\" + _strFileName;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, SavePath.c_str(), L"wb");

	// 1. DeathCount ����
	fwrite(&m_DeathCount, sizeof(int), 1, pFile);

	// 2. playtime ����
	fwrite(&m_PlayTime, sizeof(float), 1, pFile);

	// 3. Strawberry count ����
	fwrite(&m_StrawberryCnt, sizeof(int), 1, pFile);

	// 4. Strawberry table ����
	// �� array ��Ҹ��� vector�� ����
	for (int i = 0; i < (int)LEVEL_TYPE::END; ++i)
	{
		// vector ũ�� ����
		int vecSize = (int)m_StrawberryTable[i].size();
		fwrite(&vecSize, sizeof(int), 1, pFile);

		// vector ����
		fwrite(m_StrawberryTable[i].data(), sizeof(char), vecSize, pFile);
	}
}

void CSaveData::Load(const wstring& _strFileName)
{
	wstring SavePath = CPathMgr::Get()->GetSavePath();
	SavePath += L"\\" + _strFileName;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, SavePath.c_str(), L"rb");

	assert(pFile);

	// 1. DeathCount �ε�
	fread(&m_DeathCount, sizeof(int), 1, pFile);

	// 2. playtime �ε�
	fread(&m_PlayTime, sizeof(float), 1, pFile);

	// 3. Strawberry count �ε�
	fread(&m_StrawberryCnt, sizeof(int), 1, pFile);

	// 4. Strawberry table �ε�
	// �� array���� vector�� �ҷ���
	for (int i = 0; i < (int)LEVEL_TYPE::END; ++i)
	{
		// vector ũ�� �ε�
		int vecSize = 0;
		fread(&vecSize, sizeof(int), 1, pFile);

		// vector resize
		m_StrawberryTable[i].resize(vecSize);

		// vector �ε�
		fread(m_StrawberryTable[i].data(), sizeof(char), vecSize, pFile);
	}
}

