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
    virtual void LBtnDown();      // 눌려있는 상태
    virtual void LBtnUp();        // 떼지는 상태
    virtual void LBtnClicked();   // 눌렸다가 뗀 상태 (동일 버튼 상에서)

public:
    CButtonUI();
    ~CButtonUI();
};

