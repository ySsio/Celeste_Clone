#pragma once
#include "CManager.h"

class CStrawBerry;
class CPlayer;
class CSaveData;
class CSound;

class CGameMgr :
    public CManager
{
    SINGLE(CGameMgr)

private:
    CPlayer*            m_Player;

    CSaveData*          m_CurSave;
    vector<CSaveData*>  m_Saves;

    int                 m_CurRoom;

    CSound*             m_BGM;

    bool                m_GamePause;

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

    void SetBGM(CSound* _Sound) { m_BGM = _Sound; }
    CSound* GetBGM() { return m_BGM; }

    void SetRoom(int _Room) { m_CurRoom = _Room; }
    int GetRoom() { return m_CurRoom; }

    void PauseGame() { m_GamePause = true; }
    void ReleaseGame() { m_GamePause = false; }
    bool IsPause() { return m_GamePause; }

public:
    void Save();
    void Load(int Idx);

public:
    virtual void Init() override;
    void Tick();

};

