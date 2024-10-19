#pragma once
#include "CLevel.h"

class CButtonUI;
class CPanelUI;
class CImageUI;
class CLevelCardUI;
class CLevelCardUI_Collectable;
class CTextUI;

class CLevel_Select :
    public CLevel
{
private:
    vector<CButtonUI*>      m_Btns;
    int                     m_BtnIdx;
    int                     m_UIMode;

    CPanelUI*               m_Panel;

    CImageUI*               m_Hover;    // 파란 깃발

    CLevelCardUI*               m_Card;     // 레벨 카드
    CLevelCardUI_Collectable*   m_Card_Collectable; // 수집 레벨카드


    float                   m_AccTime;
    bool                    m_ToGame;

public:
    void ChangeMode(int _Mode);

public:
    virtual void Enter() override;

public:
    virtual void Tick_Derived();
    virtual void Render_Derived() {}

public:
    CLevel_Select();
    ~CLevel_Select();
};

