#pragma once
#include "CObj.h"

class CSpriteRenderer;
class CAnimator;
class CTexture;

class CPlayer :
    public CObj
{
private:
    CSpriteRenderer*    m_Sprite;
    CAnimator*          m_BangAnim;
    CAnimator*          m_BodyAnim;
    CStateMachine*      m_StateMachine;
    CCollider*          m_Collider;
    CRigidBody*         m_RigidBody;

    CTexture*           m_Buffer;

    Vec2                m_Dir;
    bool                m_DirChanged;

    BANG_COLOR          m_Color;
    float               m_ColorChangeDuration;
    int                 m_HairCount;
    CTexture*           m_HairTex;
    vector<float>       m_HairSize;
    vector<float>       m_HairOffset;
    vector<Vec2>        m_HairCurPos;
    vector<Vec2>        m_HairTargetPos;

    bool                m_PlayerDead;
    Vec2                m_BounceDir;


public:
    CAnimator* GetBangAnimator() { return m_BangAnim; }
    CAnimator* GetBodyAnimator() { return m_BodyAnim; }
	CCollider* GetCollider() { return m_Collider; }
    CRigidBody* GetRigidBody() { return m_RigidBody; }
    Vec2 GetDir() { return m_Dir; }
    bool IsDirChanged() { return m_DirChanged; }

    CTexture* GetBuffer() { return m_Buffer; }
    BANG_COLOR GetColor() { return m_Color; }

    Vec2 GetBounceDir() { return m_BounceDir; }

    void SetPlayerDead(bool _b) { m_PlayerDead = _b; }

public:
    virtual void Tick() override;
    virtual void Render() override;

public:
    void BangColorUpdate();
    void DirectionUpdate();
    void HairPosUpdate();

public:
    virtual void OnCollisionEnter(CCollider* _Col, CObj* _Other, CCollider* _OtherCol) override;
    virtual void OnCollision(CCollider* _Col, CObj* _Other, CCollider* _OtherCol) override;
    virtual void OnCollisionExit(CCollider* _Col, CObj* _Other, CCollider* _OtherCol) override;

public:
    CPlayer();
    CPlayer(const CPlayer& _other) = delete;
    ~CPlayer();
};

