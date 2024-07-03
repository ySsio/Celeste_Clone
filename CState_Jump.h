#pragma once
#include "CState.h"
class CState_Jump :
    public CState
{


public:
    virtual void PlayAnimation() override;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;

public:
    CState_Jump();
    ~CState_Jump();
};

