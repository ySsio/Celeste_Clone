#pragma once
#include "CLevelCardUI.h"

class CTextUI;

class CLevelCardUI_Collectable :
    public CLevelCardUI
{
private:
    CTextUI*    m_StrawberryCnt;
    CTextUI*    m_DeathCnt;

    int         m_StrawberryLevelCnt;
    int         m_StrawberryLevelCollectedCnt;
    int         m_DeathLevelCnt;

public:
    virtual void SetValueWithLevel(int _Level) override;

public:
    CLONE(CLevelCardUI_Collectable)
    CLevelCardUI_Collectable();
    ~CLevelCardUI_Collectable();
};

