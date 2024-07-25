#pragma once
#include "CUI.h"
class CImageUI :
    public CUI
{

public:
    virtual void Tick_DerivedUI() {};
    virtual void Render_DerivedUI() override;

public:
    CLONE(CImageUI)
    CImageUI();
    ~CImageUI();
};

