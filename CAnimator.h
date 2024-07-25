#pragma once
#include "CComponent.h"

class CAnimation;
struct tAnimFrm;

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
    void End();

    CAnimation* GetCurAnim() { return m_CurAnim; }

    const tAnimFrm& GetCurFrm();

    // 일시중지, 재개하는 함수
    void Pause() { m_Done = true; }
    void Resume() { m_Done = false; }
    void Init() { m_CurIdx = 0; m_AccTime = 0.f; }
    
    bool IsDone() { return m_Done; }

public:
    virtual void FinalTick() override;
    void Render();
    void Render(HDC _DC, bool _Player = false);
    

public:
    CLONE(CAnimator)
    CAnimator();
    CAnimator(const CAnimator& _Other);
    ~CAnimator();
};

