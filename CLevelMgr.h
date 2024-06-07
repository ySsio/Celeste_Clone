#pragma once
#include "CManager.h"

class CLevel;

class CLevelMgr :
    public CManager
{
    SINGLE(CLevelMgr)

private:
    array<CLevel*, (UINT)LEVEL_TYPE::END>     m_ArrLevel;
    LEVEL_TYPE                                m_CurLevelType;

public:
    void Tick();
    void Render(HDC _hDC);

public:
    CLevel* GetCurLevel() { return m_ArrLevel[(UINT)m_CurLevelType]; }
    void ChangeLevel(LEVEL_TYPE _Type);

public:
    virtual void Init() override;

};

