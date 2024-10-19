#pragma once
#include "CState.h"
class CState_Jump :
    public CState
{
private:

public:
    void Jump();
    void EndJump();

public:
    virtual void PlayAnimation() override;

public:
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void FinalTick() override;

public:
    CLONE_DISABLE(CState_Jump)
    CState_Jump();
    ~CState_Jump();
};

