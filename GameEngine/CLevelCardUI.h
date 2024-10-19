#pragma once
#include "CImageUI.h"

class CTextUI;

class CLevelCardUI :
    public CImageUI
{
protected:
    CImageUI*   m_Card;

    CTextUI*    m_Chapter;
    CTextUI*    m_ChapterName;
    CTextUI*    m_BottomText;


public:
    virtual void SetValueWithLevel(int _Level);

public:
    CLONE(CLevelCardUI)
    CLevelCardUI();
    ~CLevelCardUI();
};

