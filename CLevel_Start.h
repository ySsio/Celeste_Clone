#pragma once
#include "CLevel.h"
class CLevel_Start :
    public CLevel
{


public:
    virtual void Enter() override;

public:
    CLevel_Start();
    ~CLevel_Start();
};

