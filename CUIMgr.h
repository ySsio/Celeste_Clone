#pragma once
#include "CManager.h"

class CUI;

class CUIMgr :
    public CManager
{
    SINGLE(CUIMgr)

private:

public:
    virtual void Init() override;
    void Tick();

public:
    CUI* GetPriorityUI(CUI* _ParentUI);


public:
};

