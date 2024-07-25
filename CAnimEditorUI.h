#pragma once
#include "CUI.h"

class CAnimation;
class CAnimator;
struct tAnimFrm;

class CAnimEditorUI :
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
    void SetBangFrm(UINT _Frm) { m_BangFrm = _Frm; }

    UINT GetBodyFrm() { return m_BodyFrm; }
    void SetBodyFrm(UINT _Frm) { m_BodyFrm = _Frm; }

    UINT GetBangFrmCnt() { return m_BangFrmCnt; }
    void SetBangFrmCnt(UINT _FrmCnt) { m_BangFrmCnt = _FrmCnt; }

    UINT GetBodyFrmCnt() { return m_BodyFrmCnt; }
    void SetBodyFrmCnt(UINT _FrmCnt) { m_BodyFrmCnt = _FrmCnt; }

    void AddBangFrm(const tAnimFrm& _Frm);
    void AddBodyFrm(const tAnimFrm& _Frm);

    void EraseBangFrm(UINT _Frm);
    void EraseBodyFrm(UINT _Frm);

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
    CAnimEditorUI();
    ~CAnimEditorUI();
};

