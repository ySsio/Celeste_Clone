#pragma once
#include "CLevel.h"

class CButtonUI;

class CLevel_Start :
    public CLevel
{
private:
    int                 m_BtnIdx;
    int                 m_UIMode;

    array<vector<CButtonUI*>, 2>  m_Btns;

public:


public:
    virtual void Enter() override;

public:
    virtual void Tick_Derived();
    virtual void Render_Derived();

public:
    CLevel_Start();
    ~CLevel_Start();
};

