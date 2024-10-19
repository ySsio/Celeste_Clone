#include "pch.h"
#include "CSaveData.h"
#include "CPathMgr.h"

extern array<vector<LEVEL_TYPE>, LEVEL_COUNT + 3> LEVEL_MAP
{ {
	// ���ѷα�
	{ LEVEL_TYPE::PROLOGUE },
	
	// é�� 1. �������� ����
	{ LEVEL_TYPE::LEVEL_01_01, LEVEL_TYPE::LEVEL_01_02, LEVEL_TYPE::LEVEL_01_03 },

	// é�� 2. ������ ��
	{ LEVEL_TYPE::LEVEL_02_01 },

	// é�� 3. ������Ƽ�� ����Ʈ

	// é�� 4. Ȳ�� �긶��

	// é�� 5. �ſ� ���

	// é�� 6. �ݿ�

	// é�� 7. ����

	// ���ʷα�

	// é�� 8. �ھ�
} };

CSaveData::CSaveData()
	: m_PlayTime(0.f)
	, m_DeathCount(0)
	, m_StrawberryCnt(0)
	, m_DeathTable{}
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

	
	// 1. playtime ����
	fwrite(&m_PlayTime, sizeof(float), 1, pFile);

	// 2. Strawberry count ����
	fwrite(&m_StrawberryCnt, sizeof(int), 1, pFile);

	// 3. Strawberry table ����
	// �� array ��Ҹ��� vector�� ����
	for (int i = 0; i < (int)LEVEL_TYPE::END; ++i)
	{
		// vector ũ�� ����
		int vecSize = (int)m_StrawberryTable[i].size();
		fwrite(&vecSize, sizeof(int), 1, pFile);

		// vector ����
		fwrite(m_StrawberryTable[i].data(), sizeof(char), vecSize, pFile);
	}

	// 4. DeathCount ����
	fwrite(&m_DeathCount, sizeof(int), 1, pFile);

	// 5. Death table ����
	for (int i = 0; i < (int)LEVEL_TYPE::END; ++i)
	{
		fwrite(&m_DeathTable[i], sizeof(int), 1, pFile);
	}

	fclose(pFile);
}

void CSaveData::Load(const wstring& _strFileName)
{
	wstring SavePath = CPathMgr::Get()->GetSavePath();
	SavePath += L"\\" + _strFileName;

	// �̸� �ε�
	SetName(_strFileName);

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, SavePath.c_str(), L"rb");

	assert(pFile);

	// 1. playtime �ε�
	fread(&m_PlayTime, sizeof(float), 1, pFile);

	// 2. Strawberry count �ε�
	fread(&m_StrawberryCnt, sizeof(int), 1, pFile);

	// 3. Strawberry table �ε�
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

	// 4. DeathCount �ε�
	fread(&m_DeathCount, sizeof(int), 1, pFile);

	// 5. Death table �ε�
	for (int i = 0; i < (int)LEVEL_TYPE::END; ++i)
	{
		fread(&m_DeathTable[i], sizeof(int), 1, pFile);
	}

	fclose(pFile);
}

