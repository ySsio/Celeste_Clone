#pragma once
#include "CManager.h"

class CStrawBerry;
class CPlayer;
class CSaveData;

class CGameMgr :
    public CManager
{
    SINGLE(CGameMgr)

private:
    CPlayer*        m_Player;

    CSaveData*          m_CurSave;
    vector<CSaveData*>  m_Saves;

    array<int, (int)LEVEL_TYPE::END>  m_StrawberryCntTable;

public:
    CPlayer* GetPlayer() { return m_Player; }
    void SetPlayer(CPlayer* _Player) { m_Player = _Player; }

    const vector<CSaveData*>& GetSaves() { return m_Saves; }

    void SetCurSave(int _Idx) { m_CurSave = m_Saves[_Idx]; }
    void SetCurSave(CSaveData* _Save) { m_CurSave = _Save; }
	CSaveData* GetCurSave() { return m_CurSave; }

    void AddStrawberry(LEVEL_TYPE _Type, CObj* _StrawBerry);
    void AddDeathCount();

    CSaveData* AddNewSaveData();

	void ClearStrawberryCntTable(LEVEL_TYPE _Type) { m_StrawberryCntTable[(int)_Type] = 0; }

    int& GetStrawberryCnt(LEVEL_TYPE _Type) { return m_StrawberryCntTable[(int)_Type]; }

public:
    void Save();
    void Load(int Idx);

public:
    virtual void Init() override;
    void Tick();

};

