#pragma once
#include "CState.h"

class CState_Run :
    public CState
{
private:
    float   m_AccTime;
    float   m_Duration;

public:
    virtual void PlayAnimation() override;

public:
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void FinalTick() override;

public:
    CLONE_DISABLE(CState_Run)
    CState_Run();
    ~CState_Run();
};

