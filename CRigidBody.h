#pragma once
#include "CComponent.h"

class CRigidBody :
    public CComponent
{
private:
    Vec2    m_Force;
    Vec2    m_Accel;
    Vec2    m_Velocity;

    static float    m_FrictionCoef;

    float   m_Mass;

    float   m_MaxSpeed;

    static Vec2     m_GravityAccel;
    float   m_GravityCoef;
    float   m_GravityOriginalCoef;
    float   m_GravityJumpCoef;
    bool    m_Gravity;
    bool    m_Ground;
    bool    m_Jump;

    float   m_JumpSpeed;


    static Vec2     m_DashFrictionCoef;

    UINT    m_DashCount;
    UINT    m_DashMaxCount;
    float   m_DashSpeed;
    float   m_DashTime;
    float   m_DashAccTime;
    bool    m_Dash;

    Vec2    m_DashDir;

    static float    m_DeadFrictionCoef;

    bool    m_PlayerDead;



public:
    void SetForce(Vec2 _Force) { m_Force = _Force; }
    void SetVelocity(Vec2 _Velocity) { m_Velocity = _Velocity; }
    void SetMass(float _Mass) { m_Mass = _Mass; }
    void SetJumpSpeed(float _Speed) { m_JumpSpeed = _Speed; }
    void SetGravity(bool _b) { m_Gravity = _b; }
    void SetGround(bool _b) {
        m_Ground = _b;
        if (_b)
            m_DashCount = m_DashMaxCount;
    }

    void SetDead(bool _b) { m_PlayerDead = _b; }

    float GetMaxSpeed() { return m_MaxSpeed; }

    void AddForce(Vec2 _Force) { m_Force += _Force; }
    void AddVelocity(Vec2 _Velocity) { m_Velocity += _Velocity; }

    void SetDashMaxCount(UINT _Cnt) { m_DashMaxCount = _Cnt; }
    UINT GetDashMaxCount() { return m_DashMaxCount; }

    UINT GetDashLeftCount() { return m_DashCount; }

    bool CanDash() { return m_DashCount > 0; }

    Vec2 GetForce() { return m_Force; }
    Vec2 GetAccel() { return m_Accel; }
    Vec2 GetVelocity() { return m_Velocity; }
    float GetMass() { return m_Mass; }
    float GetJumpSpeed() { return m_JumpSpeed; }

    bool IsGround() { return m_Ground; }
    bool IsDash() { return m_Dash; }
    bool IsJump() { return m_Jump; }


public:
    void Jump();
    void EndJump();

    void Dash(Vec2 _Dir);

    void MovePosition(Vec2 _Pos);

public:
    virtual void FinalTick() override;

public:
    CRigidBody();
    ~CRigidBody();
};

