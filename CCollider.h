#pragma once
#include "CComponent.h"

class CCollider :
    public CComponent
{
private:
    Vec2    m_Offset;
    Vec2    m_Scale;
    Vec2    m_FinalPos;

    int     m_OverlapCount;

public:
    Vec2 GetFianlPos() { return m_FinalPos; }
    Vec2 GetScale() { return m_Scale; }

    void SetOffset(Vec2 _Offset) { m_Offset = _Offset; }
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

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

