#pragma once
#include "CState.h"
class CState_Dash :
    public CState
{
private:
    float m_AccTime;

    bool m_FirstAfterImage;
    bool m_SecondAfterImage;
    bool m_ThirdAfterImage;

public:
    virtual void PlayAnimation() override;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;

public:
    CState_Dash();
    ~CState_Dash();
};

