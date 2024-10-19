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
    LEVEL_TYPE                                m_CurLevelType;

public:
    void Tick();
    void FinalTick();
    void Render();

public:
    CLevel* GetCurLevel() { return m_CurLevel; }
	LEVEL_TYPE GetCurLevelType() { return m_CurLevelType; }
    void ChangeLevel(LEVEL_TYPE _Type);

public:
    virtual void Init() override;

};

