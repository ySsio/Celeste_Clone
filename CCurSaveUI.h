#pragma once
#include "CSaveUI.h"

class CSaveData;

class CCurSaveUI 
    : public CButtonUI
{
private:
    CSaveData*  m_SaveData;

public:
    void SetSaveData(CSaveData* _SaveData) { m_SaveData = _SaveData; }

public:
    CLONE(CCurSaveUI)
    CCurSaveUI();
    CCurSaveUI(const CCurSaveUI& _Other);
    ~CCurSaveUI();
};

