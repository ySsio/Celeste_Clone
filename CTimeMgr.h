#pragma once
#include "CManager.h"

class CTimeMgr :
    public CManager
{
    SINGLE(CTimeMgr)

private:
    LARGE_INTEGER   m_Frequency;
    LARGE_INTEGER   m_CurCount;

    float           m_fAccTime;

    int             m_FPS;

    double          m_DT;
    float           m_fDT;

public:
    double GetDT() { return m_DT; }
    float GetfDT() { return m_fDT; }
    

public:
    virtual void Init() override;
    void Tick();
    void Render();
    void FinalTick();
};

