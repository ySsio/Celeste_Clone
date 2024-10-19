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

    bool        m_Integer;
    bool        m_Float;

public:
    void AddChar(WPARAM wParam);
    void SetActive(bool _b) { m_Active = _b; }
    void SetText(const wstring& _Text) { m_Text = _Text; }
    void SetNumValue(int _Num) { m_Text = std::to_wstring(_Num); }
    void SetNumValue(float _Num) { m_Text = std::to_wstring(_Num); }
    void SetInteger(bool _b) { m_Integer = _b; SetNumValue(0); }
    void SetFloat(bool _b) { m_Float = _b; SetNumValue(0.f); }

    const wstring& GetValue() { return m_Text; }

    int GetIntValue() { 
        assert(m_Integer); 
        if (m_Text == L"") 
            return 0; 
        return std::stoi(m_Text); 
    }

    float GetFloatValue() { 
        assert(m_Float); 
        if (m_Text == L"") 
            return 0.f; 
        return std::stof(m_Text); 
    }

public:
    virtual void Tick_DerivedUI() override;
    virtual void Render_DerivedUI() override;


public:
    CLONE(CTextBoxUI)
    CTextBoxUI();
    CTextBoxUI(const CTextBoxUI& _Other);
    ~CTextBoxUI();
};


