#pragma once
#include "CLevel.h"

class CLevel_Level_01 :
    public CLevel
{
private:


public:
    virtual void Enter() override;
    virtual void Exit() override;

public:
    CLevel_Level_01();
    ~CLevel_Level_01();
};

