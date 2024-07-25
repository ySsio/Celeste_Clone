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

public:
    CPlayer* GetPlayer() { return m_Player; }
    void SetPlayer(CPlayer* _Player) { m_Player = _Player; }

    void AddStrawberry(CStrawBerry* _StrawBerry);
    void AddDeathCount();

    void AddNewSaveData();

public:
    void Save();
    void Load(int Idx);

public:
    virtual void Init() override;
    void Tick();

public:
    void SaveGame();
};

