#pragma once
#include "CManager.h"

class CStrawBerry;
class CPlayer;

class CGameMgr :
    public CManager
{
    SINGLE(CGameMgr)

private:
    CPlayer*        m_Player;

    int             m_StrawberryCnt;

    // vector index가 딸기 번호고, 그 딸기가 먹혔는지 여부를 저장
    vector<bool>    m_StrawberryTable;  

public:
    CPlayer* GetPlayer() { return m_Player; }
    void SetPlayer(CPlayer* _Player) { m_Player = _Player; }

    void AddStrawberry(CStrawBerry* _StrawBerry);

public:
    virtual void Init() override;

public:
    void SaveGame();
};

