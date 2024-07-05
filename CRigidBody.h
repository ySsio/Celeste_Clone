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
    bool    m_SpeedLimit;


    // Friction
    Vec2    m_FrictionCoef;
    bool    m_FrictionY;

    // Gravity
    static Vec2     m_GravityAccel;
    float   m_GravityCoef;
    float   m_GravityOriginalCoef;
    float   m_GravityJumpCoef;
    bool    m_Gravity;
    bool    m_Ground;
    bool    m_Jump;

    float   m_JumpSpeed;


public:
    void SetForce(Vec2 _Force) { m_Force = _Force; }
    void SetVelocity(Vec2 _Velocity) { m_Velocity = _Velocity; }
    void SetMass(float _Mass) { m_Mass = _Mass; }


    void SetSpeedLimit(bool _b) { m_SpeedLimit = _b; }

    void SetJumpSpeed(float _Speed) { m_JumpSpeed = _Speed; }
    void SetGravity(bool _b) { m_Gravity = _b; }
	void SetGround(bool _b) { m_Ground = _b; }


    void SetFrictionCoef(Vec2 _Friction) { m_FrictionCoef = _Friction; }
    void SetFrictionY(bool _b) { m_FrictionY = _b; }

    float GetMaxSpeed() { return m_MaxSpeed; }

    void AddForce(Vec2 _Force) { m_Force += _Force; }
    void AddVelocity(Vec2 _Velocity) { m_Velocity += _Velocity; }


    Vec2 GetForce() { return m_Force; }
    Vec2 GetAccel() { return m_Accel; }
    Vec2 GetVelocity() { return m_Velocity; }
    float GetMass() { return m_Mass; }
    float GetJumpSpeed() { return m_JumpSpeed; }

    bool IsGround() { return m_Ground; }
    bool IsJump() { return m_Jump; }


public:
    void Jump();
    void EndJump();

    void MovePosition(Vec2 _Pos);

public:
    virtual void FinalTick() override;

public:
    CRigidBody();
    ~CRigidBody();
};

