#include "pch.h"
#include "CGameMgr.h"

#include "CStrawBerry.h"

#include "CTimeMgr.h"
#include "CPathMgr.h"

#include "CSaveData.h"

CGameMgr::CGameMgr()
	: m_Player(nullptr)
	, m_CurSave(nullptr)
{

}

CGameMgr::~CGameMgr()
{
	Release_Vector(m_Saves);
}

void CGameMgr::AddStrawberry(CStrawBerry* _StrawBerry)
{

}

void CGameMgr::AddDeathCount()
{
	++m_CurSave->m_DeathCount;
}

void CGameMgr::AddNewSaveData()
{
	CSaveData* pSave = new CSaveData;
	m_Saves.push_back(pSave);

	wchar_t buffer[3];
	swprintf(buffer, sizeof(buffer) / sizeof(wchar_t), L"%02d", (int)m_Saves.size() - 1);

	wstring Name = L"Save" + wstring(buffer) + L".save";
	pSave->SetName(Name);
	pSave->Save(Name);
}

void CGameMgr::Save()
{
	m_CurSave->Save(m_CurSave->GetName());
}

void CGameMgr::Load(int Idx)
{
	assert(0 <= Idx && Idx < m_Saves.size());
	
	// Idx ���� save �����͸� ���� savedata�� ����
	m_CurSave = m_Saves[Idx];
}

void CGameMgr::Init()
{
	wstring SaveDir = CPathMgr::Get()->GetSavePath();
	vector<wstring> FileList = CPathMgr::Get()->GetFileList(SaveDir);

	// save ���� �ȿ� �ִ� ��� ���̺� ������ �ҷ���
	for (const auto& fileName : FileList)
	{
		CSaveData* pSave = new CSaveData;
		pSave->Load(fileName);

		m_Saves.push_back(pSave);
	}

	AddNewSaveData();
}

void CGameMgr::Tick()
{
	if (!m_CurSave)
		return;

	m_CurSave->m_PlayTime += fDT;

}

void CGameMgr::SaveGame()
{
}
