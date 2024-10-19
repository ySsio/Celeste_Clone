#pragma once
#include "CStrawBerry.h"

class CWingBerry :
    public CStrawBerry
{
private:

    bool    m_FlyAway;
    bool    m_SoundPlayed;
    float   m_SoundDuration;
    float   m_AccTime;

public:
    virtual void SetGhost(bool _b) override;

public:
    virtual void Tick() override;
    
public:
    virtual bool Init() override;

public:
    virtual bool Save(FILE* _pFile) override;

public:
    CLONE(CWingBerry)
    CWingBerry();
    ~CWingBerry();
};

