#pragma once
#include "CComponent.h"

class CRigidBody :
    public CComponent
{
private:
    Vec2    m_Force;
    Vec2    m_Accel;
    Vec2    vVelocity;

    float   m_Mass;

    static Vec2     m_GravityAccel;
    bool    m_Gravity;
    bool    m_Ground;
    float   m_JumpSpeed;


public:
    void SetForce(Vec2 _Force) { m_Force = _Force; }
    void SetAccel(Vec2 _Accel) { m_Accel = _Accel; }
    void SetVelocity(Vec2 _Velocity) { vVelocity = _Velocity; }
    void SetMass(float _Mass) { m_Mass = _Mass; }
    void SetJumpSpeed(float _Speed) { m_JumpSpeed = _Speed; }
    void SetGravity(bool _b) { m_Gravity = _b; }
    void SetGround(bool _b) { m_Ground = _b; }

    void AddForce(Vec2 _Force) { m_Force += _Force; }
    void AddAccel(Vec2 _Accel) { m_Accel += _Accel; }
    void AddVelocity(Vec2 _Velocity) { vVelocity += _Velocity; }

    Vec2 GetForce() { return m_Force; }
    Vec2 GetAccel() { return m_Accel; }
    Vec2 GetVelocity() { return vVelocity; }
    float GetMass() { return m_Mass; }
    float GetJumpSpeed() { return m_JumpSpeed; }
    bool IsGround() { return m_Ground; }

public:
    void Jump();

public:
    virtual void FinalTick() override;

public:
    CRigidBody();
    ~CRigidBody();
};

