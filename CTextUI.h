#pragma once
#include "CUI.h"

class CTextUI :
    public CUI
{
private:
    wstring     m_Text;

    HFONT       m_Font;


public:
    const wstring& GetText() { return m_Text; }

    void SetText(const wstring& _Text);

    void SetFont(const wstring& _Font, UINT _Size);

public:
    virtual void Tick_DerivedUI() override;
    virtual void Render_DerivedUI() override;


public:
    CTextUI();
    ~CTextUI();
};

