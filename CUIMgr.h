#pragma once
#include "CManager.h"

class CUI;
class CTextBoxUI;

class CUIMgr :
    public CManager
{
    SINGLE(CUIMgr)

private:
    CTextBoxUI*  m_ActivatedTextBox;

public:
    CTextBoxUI* GetActivatedTextBox() { return m_ActivatedTextBox; }

public:
    virtual void Init() override;
    void Tick();

public:
    CUI* GetPriorityUI(CUI* _ParentUI);


public:
};

