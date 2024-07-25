#pragma once
#include "CState.h"

class CState_Idle :
    public CState
{
private:
    vector<wstring>     m_BangAnimList;
    vector<wstring>     m_BodyAnimList;
    list<int>           m_AnimPlayList;

public:
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void FinalTick() override;

public:
    virtual void PlayAnimation() override;

public:
    CLONE_DISABLE(CState_Idle)
    CState_Idle();
    ~CState_Idle();
};

