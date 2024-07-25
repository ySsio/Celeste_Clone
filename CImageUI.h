#pragma once
#include "CUI.h"
class CImageUI :
    public CUI
{

public:
    virtual void Render_DerivedUI() override;

public:
    CImageUI();
    ~CImageUI();
};

