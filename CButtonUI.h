#pragma once
#include "CUI.h"


class CButtonUI :
    public CUI
{
private:
    function<void(void)>    m_Function;

public:
    void SetFunction(function<void(void)> _Func) { m_Function = _Func; }

public:
    virtual void Tick_DerivedUI() override;
    virtual void Render_DerivedUI() override;

public:
    virtual void LBtnDown();      // �����ִ� ����
    virtual void LBtnUp();        // ������ ����
    virtual void LBtnClicked();   // ���ȴٰ� �� ���� (���� ��ư �󿡼�)

public:
    CButtonUI();
    ~CButtonUI();
};

