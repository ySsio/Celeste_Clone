#pragma once
#include "CUI.h"

class CAnimation;
class CAnimator;

class CAnimUI :
    public CUI
{
private:
    CAnimation*     m_Bang;
    CAnimation*     m_Body;

    UINT            m_BangFrm;
    UINT            m_BodyFrm;

    UINT            m_BangFrmCnt;
    UINT            m_BodyFrmCnt;

    bool            m_Play;

public:
    CAnimation* GetBang() { return m_Bang; }
    void SetBang(CAnimation* _Tex);

    CAnimation* GetBody() { return m_Body; }
    void SetBody(CAnimation* _Tex);

    UINT GetBangFrm() { return m_BangFrm; }
    UINT GetBodyFrm() { return m_BodyFrm; }

    UINT GetBangFrmCnt() { return m_BangFrmCnt; }
    UINT GetBodyFrmCnt() { return m_BodyFrmCnt; }

    void Play() { m_Play = true; }
    void Stop() { m_Play = false; }

    void IncrBangFrm()
    {
        if (m_BangFrm == m_BangFrmCnt - 1)
            m_BangFrm = 0;
        else
            ++m_BangFrm;
    }

    void DecrBangFrm()
    {
        if (m_BangFrm == 0)
            m_BangFrm = m_BangFrmCnt - 1;
        else
            --m_BangFrm;
    }

    void IncrBodyFrm()
    {
        if (m_BodyFrm == m_BodyFrmCnt - 1)
            m_BodyFrm = 0;
        else
            ++m_BodyFrm;
    }

    void DecrBodyFrm()
    {
        if (m_BodyFrm == 0)
            m_BodyFrm = m_BodyFrmCnt - 1;
        else
            --m_BodyFrm;
    }

public:
    virtual void Tick_DerivedUI() override;
    virtual void Render_DerivedUI() override;


public:
    CAnimUI();
    ~CAnimUI();
};

