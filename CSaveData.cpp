#include "pch.h"
#include "CSaveData.h"
#include "CPathMgr.h"

extern array<vector<LEVEL_TYPE>, LEVEL_COUNT + 3> LEVEL_MAP
{ {
	{ LEVEL_TYPE::LEVEL_00 },
	{ LEVEL_TYPE::LEVEL_01_01, LEVEL_TYPE::LEVEL_01_02, LEVEL_TYPE::LEVEL_01_03 },
	{ LEVEL_TYPE::LEVEL_02_01 },
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
	// 이름 설정
	SetName(_strFileName);

	wstring SavePath = CPathMgr::Get()->GetSavePath();
	SavePath += L"\\" + _strFileName;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, SavePath.c_str(), L"wb");

	
	// 1. playtime 저장
	fwrite(&m_PlayTime, sizeof(float), 1, pFile);

	// 2. Strawberry count 저장
	fwrite(&m_StrawberryCnt, sizeof(int), 1, pFile);

	// 3. Strawberry table 저장
	// 각 array 요소마다 vector을 저장
	for (int i = 0; i < (int)LEVEL_TYPE::END; ++i)
	{
		// vector 크기 저장
		int vecSize = (int)m_StrawberryTable[i].size();
		fwrite(&vecSize, sizeof(int), 1, pFile);

		// vector 저장
		fwrite(m_StrawberryTable[i].data(), sizeof(char), vecSize, pFile);
	}

	// 4. DeathCount 저장
	fwrite(&m_DeathCount, sizeof(int), 1, pFile);

	// 5. Death table 저장
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

	// 이름 로드
	SetName(_strFileName);

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, SavePath.c_str(), L"rb");

	assert(pFile);

	// 1. playtime 로드
	fread(&m_PlayTime, sizeof(float), 1, pFile);

	// 2. Strawberry count 로드
	fread(&m_StrawberryCnt, sizeof(int), 1, pFile);

	// 3. Strawberry table 로드
	// 각 array마다 vector을 불러옴
	for (int i = 0; i < (int)LEVEL_TYPE::END; ++i)
	{
		// vector 크기 로드
		int vecSize = 0;
		fread(&vecSize, sizeof(int), 1, pFile);

		// vector resize
		m_StrawberryTable[i].resize(vecSize);

		// vector 로드
		fread(m_StrawberryTable[i].data(), sizeof(char), vecSize, pFile);
	}

	// 4. DeathCount 로드
	fread(&m_DeathCount, sizeof(int), 1, pFile);

	// 5. Death table 로드
	for (int i = 0; i < (int)LEVEL_TYPE::END; ++i)
	{
		fread(&m_DeathTable[i], sizeof(int), 1, pFile);
	}

	fclose(pFile);
}

