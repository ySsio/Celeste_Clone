#pragma once
#include "CState.h"

class CDeadEffect;

class CState_Dead :
    public CState
{
private:
    Vec2    m_BounceDir;

    float   m_AccTime;
    float   m_AnimDuration;
    float   m_RespawnDuration;

    float   m_SpreadDuration;
    float   m_GatherWaitTime;

    Vec2    m_SpawnPoint;

    bool    m_LevelReset;

    bool    m_SpreadEffect;
    bool    m_Respawn;
    bool    m_GatherEffect;

    CDeadEffect* m_DeadEffect;

public:
    virtual void PlayAnimation() override;

public:
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void FinalTick() override;

public:
    CLONE_DISABLE(CState_Dead)
    CState_Dead();
    ~CState_Dead();
};

