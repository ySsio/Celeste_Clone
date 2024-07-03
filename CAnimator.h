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

    bool    m_Done;

public:
    void AddAnimation(const wstring& _AnimName, CAnimation* _Anim) { m_MapAnim.emplace(_AnimName, _Anim); }
    void Play(const wstring& _AnimName, bool _Repeat = false);

    void Pause();
    
    bool IsDone() { return m_Done; }

public:
    virtual void FinalTick() override;
    void Render();
    void Render(HDC _DC, bool _Player = false);
    

public:
    CAnimator();
    ~CAnimator();
};

