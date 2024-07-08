#pragma once
#include "CObj.h"

class CSpring :
    public CObj
{
private:
    CAnimator*  m_Animator;

    CCollider*  m_Collider;

    Vec2        m_Dir;

    Vec2        m_BouncePos;


public:
    void SetDir(Vec2 _Dir) { m_Dir = _Dir; }

    Vec2 GetDir() { return m_Dir; }

public:
    virtual void Tick() override;
    virtual void Render() override;

public:
    virtual void OnCollisionEnter(CCollider* _Col, CObj* _Other, CCollider* _OtherCol);


public:
    CSpring();
    ~CSpring();
};

