#pragma once
#include "CState.h"

class CState_Idle :
    public CState
{
private:
    vector<wstring>     m_AnimList;
    list<int>           m_AnimPlayList;
    float               m_curAnimDuration;
    float               m_AccTime;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;

public:
    void PlayNextAnim();

public:
    CState_Idle();
    ~CState_Idle();
};

