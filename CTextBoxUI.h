#pragma once
#include "CUI.h"

class CTextBoxUI :
    public CUI
{
private:
    wstring     m_Text;
    UINT        m_CursorPos;
    bool        m_Active;
    bool        m_CursorVisible;

public:
    void AddChar(WPARAM wParam);
    void SetActive(bool _b) { m_Active = _b; }

public:
    virtual void Tick_DerivedUI() override;
    virtual void Render_DerivedUI() override;


public:
    CTextBoxUI();
    ~CTextBoxUI();
};


