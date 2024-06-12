#pragma once
#include "CComponent.h"

class CAnimation;

class CAnimator :
    public CComponent
{
private:
    unordered_map<wstring, CAnimation*>     m_MapAnim;
    CAnimation*                             m_CurAnim;

    float   m_AccTime;

    UINT    m_CurIdx;
    UINT    m_FrmCnt;

    bool    m_Repeat;

public:
    void AddAnimation(const wstring& _AnimName, CAnimation* _Anim) { m_MapAnim.emplace(_AnimName, _Anim); }
    float Play(const wstring& _AnimName, bool _Repeat = true);

public:
    virtual void FinalTick() override;
    void Render();

public:
    CAnimator();
    ~CAnimator();
};

