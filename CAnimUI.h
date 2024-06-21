#pragma once
#include "CUI.h"

class CAnimation;

class CAnimUI :
    public CUI
{
private:
    CAnimation*     m_Bang;
    CAnimation*     m_Body;

    UINT            m_BangFrm;
    UINT            m_BodyFrm;

    UINT            m_BangMaxFrm;
    UINT            m_BodyMaxFrm;

public:
    CAnimation* GetBang() { return m_Bang; }
    void SetBang(CAnimation* _Tex);

    CAnimation* GetBody() { return m_Body; }
    void SetBody(CAnimation* _Tex);

public:
    virtual void Tick_DerivedUI() override;
    virtual void Render_DerivedUI() override;


public:
    CAnimUI();
    ~CAnimUI();
};

