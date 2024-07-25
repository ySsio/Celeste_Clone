#pragma once
#include "CLevel.h"
class CLevel_Editor :
    public CLevel
{
protected:
    HMENU   m_Menu;

public:
    virtual void Enter() override;

public:
    virtual void Tick_Derived() override;


public:
    CLONE_DISABLE(CLevel_Editor)
    CLevel_Editor();
    ~CLevel_Editor();
};

