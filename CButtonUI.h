#pragma once
#include "CUI.h"


class CButtonUI :
    public CUI
{
private:
    function<void(void)>    m_Function;
    int                     m_FontSize;
    HFONT                   m_Font;

public:
    void SetFunction(function<void(void)> _Func) { m_Function = _Func; }
    void SetFontSize(int _Size);

public:
    virtual void Tick_DerivedUI() override;
    virtual void Render_DerivedUI() override;

public:
    virtual void LBtnDown();      // �����ִ� ����
    virtual void LBtnUp();        // ������ ����
    virtual void LBtnClicked();   // ���ȴٰ� �� ���� (���� ��ư �󿡼�)

public:
    CLONE(CButtonUI)
    CButtonUI();
    ~CButtonUI();
};

