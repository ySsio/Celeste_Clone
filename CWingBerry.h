#pragma once
#include "CStrawBerry.h"

class CWingBerry :
    public CStrawBerry
{
private:
    int     m_OriRoom;
    bool    m_FlyAway;

public:
    virtual void SetGhost(bool _b) override;

public:
    virtual void Tick() override;
    
public:
    virtual void Init() override;

public:
    virtual bool Save(FILE* _pFile) override;

public:
    CLONE(CWingBerry)
    CWingBerry();
    ~CWingBerry();
};

