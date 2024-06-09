#pragma once
#include "CObj.h"

class CSpriteRenderer;
class CAnimator;

class CPlayer :
    public CObj
{
private:
    CSpriteRenderer*    m_HeadSprite;
    CAnimator*          m_HeadAnim;
    CAnimator*          m_BodyAnim;
    CCollider*          m_Collider;
    CRigidBody*         m_RigidBody;

public:
    virtual void Tick() override;
    virtual void Render() override;

public:
    virtual void OnCollisionEnter(CCollider* _Col, CObj* _Other, CCollider* _OtherCol) override;
    virtual void OnCollision(CCollider* _Col, CObj* _Other, CCollider* _OtherCol) override;
    virtual void OnCollisionExit(CCollider* _Col, CObj* _Other, CCollider* _OtherCol) override;

public:
    CPlayer();
    CPlayer(const CPlayer& _other) = delete;
    ~CPlayer();
};

