#pragma once
#include "CLevel_Editor.h"

class CAnimUI;
class CAnimation;

class CLevel_AnimEditor :
    public CLevel_Editor
{
private:
    CAnimUI* m_AnimUI;

public:
    virtual void Enter() override;

public:
    void SetBangAnim(CAnimation* _Anim);
    void SetBodyAnim(CAnimation* _Anim);



public:
    void CreateAnimation();
    void SaveAnimation();
    void LoadAnimation();


public:
    CLevel_AnimEditor();
    ~CLevel_AnimEditor();
};

