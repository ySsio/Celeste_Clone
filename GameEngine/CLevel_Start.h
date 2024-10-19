#pragma once
#include "CLevel.h"

class CButtonUI;
class CPanelUI;

class CLevel_Start :
    public CLevel
{
private:
    int                 m_BtnIdx;
    int                 m_UIMode;

    CPanelUI*           m_PanelUI;

    array<vector<CButtonUI*>, 2>  m_Btns;

public:
    void ChangeMode(int _Mode);

    void SelectBtn(int _Idx);
    void DeselectBtn(int _Idx);

public:
    virtual void Enter() override;

public:
    virtual void Tick_Derived();
    virtual void Render_Derived();

public:
    CLevel_Start();
    ~CLevel_Start();
};

