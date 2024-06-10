#pragma once
#include "CComponent.h"

class CRigidBody :
    public CComponent
{
private:
    Vec2    m_Force;
    Vec2    m_Accel;
    Vec2    m_Velocity;

    float   m_Mass;

    float   m_MaxSpeed;

    static Vec2     m_GravityAccel;
    float   m_GravityCoef;
    bool    m_Gravity;
    bool    m_Ground;

    float   m_JumpSpeed;
    float   m_MaxJumpSpeed;

    float   m_MaxJumpDuration;
    float   m_JumpAccTime;

    bool    m_JumpEnd;

    static float    m_FrictionCoef;


    float   m_DashSpeed;
    float   m_DashTime;
    float   m_DashAccTime;
    bool    m_Dash;


public:
    void SetForce(Vec2 _Force) { m_Force = _Force; }
    void SetAccel(Vec2 _Accel) { m_Accel = _Accel; }
    void SetVelocity(Vec2 _Velocity) { m_Velocity = _Velocity; }
    void SetMass(float _Mass) { m_Mass = _Mass; }
    void SetJumpSpeed(float _Speed) { m_JumpSpeed = _Speed; }
    void SetGravity(bool _b) { m_Gravity = _b; }
    void SetGround(bool _b) { m_Ground = _b; }
    void SetJumpAccTime(float _Time) { m_JumpAccTime = 0.f; }

    void AddForce(Vec2 _Force) { m_Force += _Force; }
    void AddAccel(Vec2 _Accel) { m_Accel += _Accel; }
    void AddVelocity(Vec2 _Velocity) { m_Velocity += _Velocity; }

    void SetJumpEnd(bool _b) { m_JumpEnd = _b; }

    Vec2 GetForce() { return m_Force; }
    Vec2 GetAccel() { return m_Accel; }
    Vec2 GetVelocity() { return m_Velocity; }
    float GetMass() { return m_Mass; }
    float GetJumpSpeed() { return m_JumpSpeed; }
    bool IsGround() { return m_Ground; }


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

