#pragma once
#include "CUI.h"

class CAnimation;

class CAnimUI :
    public CUI
{
private:
    CAnimator* m_Anim;

public:
    void SetAnim(const wstring& _AnimName, CAnimation* _Anim);


public:
    virtual void Render_DerivedUI() override;


public:
    CAnimUI();
    ~CAnimUI();

};

