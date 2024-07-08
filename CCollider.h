#pragma once
#include "CComponent.h"

class CCollider :
    public CComponent
{
private:
    Vec2    m_Offset;
    Vec2    m_Scale;
    Vec2    m_FinalPos;

    bool    m_Trigger;

    int     m_OverlapCount;

public:
    Vec2 GetOffset() { return m_Offset; }
    Vec2 GetFinalPos() { return m_FinalPos; }
    Vec2 GetScale() { return m_Scale; }
    int GetOverlapCount() { return m_OverlapCount; }

    void SetOffset(Vec2 _Offset) { m_Offset = _Offset; }
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

    bool IsTrigger() { return m_Trigger; }
    void SetTrigger(bool _b) { m_Trigger = _b; }

public:
    virtual void FinalTick() override;

public:
    void BeginOverlap(CCollider* _Other);
    void Overlap(CCollider* _Other);
    void EndOverlap(CCollider* _Other);


public:
    CCollider();
    ~CCollider();
};

