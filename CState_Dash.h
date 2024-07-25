#pragma once
#include "CState.h"
class CState_Dash :
    public CState
{
private:
    float   m_AccTime;

    bool    m_FirstAfterImage;
    bool    m_SecondAfterImage;
    bool    m_ThirdAfterImage;

    float   m_DashSpeed;

    UINT    m_AfterImageColor;
    

public:
    void SetDashSpeed(float _Speed) { m_DashSpeed = _Speed; }
    

public:
    void Dash();

public:
    virtual void PlayAnimation() override;

public:
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void FinalTick() override;

public:
    CLONE_DISABLE(CState_Dash)
    CState_Dash();
    ~CState_Dash();
};

