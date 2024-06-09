#pragma once
#include "CLevel.h"
class CLevel_Editor :
    public CLevel
{

public:
    virtual void Enter() override;

public:
    CLevel_Editor();
    ~CLevel_Editor();
};

