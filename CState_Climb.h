#pragma once
#include "CState.h"
class CState_Climb :
    public CState
{
private:


public:
    virtual void PlayAnimation() override;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;

public:
    CState_Climb();
    ~CState_Climb();
};

