#pragma once
#include "CManager.h"

class CLevel;

class CLevelMgr :
    public CManager
{
    SINGLE(CLevelMgr)

private:
    array<CLevel*, (UINT)LEVEL_TYPE::END>     m_ArrLevel;
    CLevel*                                   m_CurLevel;

public:
    void Tick();
    void FinalTick();
    void Render();

public:
    CLevel* GetCurLevel() { return m_CurLevel; }
    void ChangeLevel(CLevel* _Level);

public:
    virtual void Init() override;

};

