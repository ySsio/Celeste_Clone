#pragma once
#include "CLevel_Editor.h"

class CAnimation;

class CLevel_AnimEditor :
    public CLevel_Editor
{
private:
    CAnimation* m_Animation;


public:
    virtual void Enter() override;


public:
    void CreateAnimation();
    void SaveAnimation();
    void LoadAnimation();


public:
    CLevel_AnimEditor();
    ~CLevel_AnimEditor();
};

