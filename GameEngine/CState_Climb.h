#pragma once
#include "CState.h"
class CState_Climb :
    public CState
{
private:
    bool    m_Warning;

    float   m_SlideWaitTime;
    float   m_AccTime;

public:
    virtual void Reset() override { m_AccTime = 0.f; m_Warning = false; }

public:
    virtual void PlayAnimation() override;

public:
    void Slide(bool _Warning);

public:
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void FinalTick() override;

public:
    CLONE_DISABLE(CState_Climb)
    CState_Climb();
    ~CState_Climb();
};

