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


public:
    CLevel_Editor();
    ~CLevel_Editor();
};

