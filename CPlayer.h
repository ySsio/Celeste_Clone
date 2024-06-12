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
    CStateMachine*      m_StateMachine;
    CCollider*          m_Collider;
    CRigidBody*         m_RigidBody;

    Vec2                m_Dir;

public:
    CAnimator* GetAnimator() { return m_BodyAnim; }
	CCollider* GetCollider() { return m_Collider; }
    CRigidBody* GetRigidBody() { return m_RigidBody; }
    Vec2 GetDir() { return m_Dir; }

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

