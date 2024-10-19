#pragma once
#include "CSaveUI.h"

class CSaveData;

class CCurSaveUI 
    : public CButtonUI
{
private:
    CSaveData*  m_SaveData;

public:


public:
    CLONE(CCurSaveUI)
    CCurSaveUI(CSaveData* _SaveData);
    CCurSaveUI(const CCurSaveUI& _Other);
    ~CCurSaveUI();
};

