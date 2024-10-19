#pragma once
#include "CPanelUI.h"

class CTextUI;

class CGamePauseUI :
    public CPanelUI
{
private:
    bool                m_Activate;
    vector<CTextUI*>    m_Btns;
    int                 m_BtnIdx;

public:
    virtual void Tick_DerivedUI() override;

public:
    CLONE_DISABLE(CGamePauseUI)
    CGamePauseUI();
    ~CGamePauseUI();
};

