#pragma once
#include "CState.h"

class CState_Run :
    public CState
{
private:
    float   m_Dir;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;

public:
    CState_Run();
    ~CState_Run();
};

