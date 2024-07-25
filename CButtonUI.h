#pragma once
#include "CUI.h"


class CButtonUI :
    public CUI
{
private:
    function<void(void)>    m_Function;
    HFONT                   m_Font;

public:
    void SetFunction(function<void(void)> _Func) { m_Function = _Func; }
    void SetFont(const wstring& _Name, int _Size);

    function<void(void)> GetFunction() { return m_Function; }

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

