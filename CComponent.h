#pragma once
#include "CBase.h"

class CObj;

class CComponent :
    public CBase
{
private:
    CObj*       m_Owner;

public:
    CObj* GetOwner() { return m_Owner; }
    void SetOwner(CObj* _Owner) { m_Owner = _Owner; }

public:
    virtual void FinalTick() {}

public:
    CComponent();
    ~CComponent();
};

