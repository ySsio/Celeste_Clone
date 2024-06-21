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

    UINT            m_BangMaxFrm;
    UINT            m_BodyMaxFrm;

    bool            m_Play;

public:
    CAnimation* GetBang() { return m_Bang; }
    void SetBang(CAnimation* _Tex);

    CAnimation* GetBody() { return m_Body; }
    void SetBody(CAnimation* _Tex);

    UINT GetBangFrm() { return m_BangFrm; }
    UINT GetBodyFrm() { return m_BodyFrm; }

    void Play() { m_Play = true; }
    void Stop() { m_Play = false; }

    void IncrBangFrm() { if (m_BangFrm == m_BangMaxFrm - 1) m_BangFrm = 0; ++m_BangFrm; }
    void DecrBangFrm() { if (m_BangFrm == 0) m_BangFrm = m_BangMaxFrm - 1; --m_BangFrm; }
	void IncrBodyFrm() { if (m_BodyFrm == m_BodyMaxFrm - 1) m_BodyFrm = 0; ++m_BodyFrm; }
	void DecrBodyFrm() { if (m_BodyFrm == 0) m_BodyFrm = m_BodyMaxFrm - 1; --m_BodyFrm; }

public:
    virtual void Tick_DerivedUI() override;
    virtual void Render_DerivedUI() override;


public:
    CAnimUI();
    ~CAnimUI();
};

