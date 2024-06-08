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

public:
    void AddAnimation(const wstring& _AnimName, CAnimation* _Anim) { m_MapAnim.emplace(_AnimName, _Anim); }
    void Play(const wstring& _AnimName);

public:
    virtual void FinalTick() override;
    void Render();

public:
    CAnimator();
    ~CAnimator();
};

