#pragma once
#include "CState.h"
class CState_Bounce :
    public CState
{
private:
    Vec2        m_Dir;

    float       m_BounceSpeed;

public:
    void SetDir(Vec2 _Dir) { m_Dir = _Dir; }

public:
    virtual void PlayAnimation() override;

public:
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void FinalTick() override;


public:
    CState_Bounce();
    ~CState_Bounce();
};

