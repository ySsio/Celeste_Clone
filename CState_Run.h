#pragma once
#include "CState.h"

class CState_Run :
    public CState
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;

public:
    CState_Run();
    ~CState_Run();
};

