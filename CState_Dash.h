#pragma once
#include "CState.h"
class CState_Dash :
    public CState
{
private:

public:
    virtual void Enter() override;
    virtual void FinalTick() override;

public:
    CState_Dash();
    ~CState_Dash();
};

