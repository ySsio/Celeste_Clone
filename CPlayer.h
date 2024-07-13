#pragma once
#include "CObj.h"

class CSpriteRenderer;
class CAnimator;
class CTexture;

class CPlayer :
    public CObj
{
private:
    // Component
    CSpriteRenderer*    m_Tex;
    CAnimator*          m_BangAnim;
    CAnimator*          m_BodyAnim;
    CStateMachine*      m_StateMachine;
    CCollider*          m_Collider;
    CCollider*          m_WallDetector;
    CRigidBody*         m_RigidBody;

    // Buffer
    CTexture*           m_Buffer;

    // Direction
    Vec2                m_Dir;
    bool                m_DirChanged;
    bool                m_DirFix;

    // Dash
    UINT                m_DashMaxCount;
    UINT                m_DashCount;

    // Ground
    bool                m_IsGround;

    // Wall
    bool                m_IsWall;   // WallDetector가 충돌이 일어나면
    
    // ColUpdate
    bool                m_ColUpdated;


    // Hair
    BANG_COLOR          m_Color;
    float               m_ColorChangeDuration;
    int                 m_HairCount;
    CTexture*           m_HairTex;
    vector<float>       m_HairSize;
    vector<float>       m_HairOffset;
    vector<Vec2>        m_HairCurPos;
    vector<Vec2>        m_HairTargetPos;

    // Dead
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

    UINT GetDashCount() { return m_DashCount; }

    void SetDirFix(bool _b) { m_DirFix = _b; }


    void SetDashMaxCount(UINT _Count) { m_DashMaxCount = _Count; }
    void SetDashCount(UINT _Count) { m_DashCount = _Count; }
    void SubtractDashCount() { if (m_DashCount == 0) return; --m_DashCount; }

    void SetPlayerDead(bool _b) { m_PlayerDead = _b; }

    bool CanJump() { return m_IsGround || m_IsWall; }
    bool IsGround() { return m_IsGround; }
    bool IsWall() { return m_IsWall; }

    void ResetDash() { m_DashCount = m_DashMaxCount; }

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

