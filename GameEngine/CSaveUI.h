#pragma once
#include "CButtonUI.h"

class CImageUI;

class CSaveUI :
    public CButtonUI
{
public:
    virtual void Tick_DerivedUI() override {};
    virtual void Render_DerivedUI() override;

public:
    CLONE(CSaveUI)
    CSaveUI();
    ~CSaveUI();
};

