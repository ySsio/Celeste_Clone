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
    void CreateBangAnimation();
    void SaveBangAnimation(const wstring& _strRelativePath);
    void LoadBangAnimation();

    void CreateBodyAnimation();
    void SaveBodyAnimation(const wstring& _strRelativePath);
    void LoadBodyAnimation();


public:
    CLevel_AnimEditor();
    ~CLevel_AnimEditor();
};

