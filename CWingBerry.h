#pragma once
#include "CStrawBerry.h"

class CWingBerry :
    public CStrawBerry
{

public:
    virtual void SetGhost(bool _b) override;

public:
    virtual void Tick() override;
    
public:
    virtual void Init() override;

public:
    CLONE(CWingBerry)
    CWingBerry();
    ~CWingBerry();
};

