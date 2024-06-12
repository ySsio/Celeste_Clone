#pragma once
#include "CState.h"
class CState_Hang :
    public CState
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;

public:
    CState_Hang();
    ~CState_Hang();
};

