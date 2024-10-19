#pragma once
#include "CUI.h"

class CTextUI :
    public CUI
{
private:
    wstring     m_Text;

    HFONT       m_Font;
    COLORREF    m_Color;


public:
    const wstring& GetText() { return m_Text; }

    void SetText(const wstring& _Text);

    void SetFont(const wstring& _Font, UINT _Size);
    void SetColor(COLORREF _Color) { m_Color = _Color; }

public:
    virtual void Tick_DerivedUI() override;
    virtual void Render_DerivedUI() override;


public:
    CLONE(CTextUI);
    CTextUI();
    ~CTextUI();
};

