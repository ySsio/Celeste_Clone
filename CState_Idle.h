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
    virtual void FinalTick() override;

public:
    void PlayNextAnim();

public:
    CState_Idle();
    ~CState_Idle();
};

