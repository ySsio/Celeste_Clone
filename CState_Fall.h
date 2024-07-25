#pragma once
#include "CState.h"
class CState_Fall :
    public CState
{
private:

public:
    virtual void PlayAnimation() override;

public:
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void FinalTick() override;

public:
    CLONE_DISABLE(CState_Fall)
    CState_Fall();
    ~CState_Fall();
};

