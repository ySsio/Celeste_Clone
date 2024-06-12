#pragma once
#include "CLevel_Editor.h"


class CLevel_AnimEditor :
    public CLevel_Editor
{
private:
    CAnimation* m_Animation;

private:
    void CreateAnimation();
    void SaveAnimation();
    void LoadAnimation();


public:
    CLevel_AnimEditor();
    ~CLevel_AnimEditor();
};

