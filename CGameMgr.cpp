#include "pch.h"
#include "CGameMgr.h"

#include "CStrawBerry.h"

#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CLevelMgr.h"

#include "CSaveData.h"

CGameMgr::CGameMgr()
	: m_Player(nullptr)
	, m_CurSave(nullptr)
{

}

CGameMgr::~CGameMgr()
{
	Save();

	Release_Vector(m_Saves);
}

// 게임 제작용
void CGameMgr::AddStrawberry(LEVEL_TYPE _Type, CObj* _StrawBerry)
{
	// 딸기 카운트 테이블에 집계
	++m_StrawberryCntTable[(int)_Type];

	if (!m_CurSave)
		return;

	// 딸기 카운트가 테이블 사이즈보다 크면 새로운 딸기가 추가되었음을 의미함.
	// 따라서 딸기 수집여부 테이블에도 추가해줌
	if (m_StrawberryCntTable[(int)_Type]
		> m_CurSave->GetStrawberryTable(_Type).size())
	{
		m_CurSave->GetStrawberryTable(_Type).push_back(0);
	}
}

void CGameMgr::AddDeathCount()
{
	// 레벨마다 데스 수 기록
	++m_CurSave->m_DeathTable[(int)CLevelMgr::Get()->GetCurLevelType()];

	// 전체 데스 수 기록
	++m_CurSave->m_DeathCount;
}

CSaveData* CGameMgr::AddNewSaveData()
{
	CSaveData* pSave = new CSaveData;
	m_Saves.push_back(pSave);

	wchar_t buffer[3];
	swprintf(buffer, sizeof(buffer) / sizeof(wchar_t), L"%02d", (int)m_Saves.size() - 1);

	wstring Name = L"Save" + wstring(buffer) + L".save";
	pSave->Save(Name);

	return pSave;
}



void CGameMgr::Save()
{
	if (m_CurSave)
		m_CurSave->Save(m_CurSave->GetName());
}

void CGameMgr::Load(int Idx)
{
	assert(0 <= Idx && Idx < m_Saves.size());
	
	// Idx 번쨰 save 데이터를 현재 savedata로 설정
	m_CurSave = m_Saves[Idx];
}

void CGameMgr::Init()
{
	wstring SaveDir = CPathMgr::Get()->GetSavePath();
	vector<wstring> FileList = CPathMgr::Get()->GetFileList(SaveDir);

	// save 폴더 안에 있는 모든 세이브 파일을 불러옴
	for (const auto& fileName : FileList)
	{
		CSaveData* pSave = new CSaveData;
		pSave->Load(fileName);

		m_Saves.push_back(pSave);
	}
}

void CGameMgr::Tick()
{
	if (!m_CurSave)
		return;

	m_CurSave->m_PlayTime += fDT;

}