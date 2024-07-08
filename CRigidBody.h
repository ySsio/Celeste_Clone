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
    bool    m_FrictionX;
    bool    m_FrictionY;

    // Gravity
    static Vec2     m_GravityAccel;
    float   m_GravityCoef;
    float   m_GravityOriginalCoef;
    float   m_GravityJumpCoef;
    bool    m_Gravity;

    float   m_JumpSpeed;

    // AutoMove (나를 따라와야되는 녀석을 등록)
    CObj*     m_Follower;


public:
    void SetForce(Vec2 _Force) { m_Force = _Force; }
    void SetVelocity(Vec2 _Velocity) { m_Velocity = _Velocity; }
    void SetMass(float _Mass) { m_Mass = _Mass; }

    void SetMaxSpeed(float _Speed) { m_MaxSpeed = _Speed; }
    void SetSpeedLimit(bool _b) { m_SpeedLimit = _b; }

    void SetGravity(bool _b) { m_Gravity = _b; }

    void SetGravityCoef(float _Coef) { m_GravityCoef = _Coef; }


    void SetFrictionCoef(Vec2 _Friction) { m_FrictionCoef = _Friction; }
    void SetFrictionX(bool _b) { m_FrictionX = _b; }
    void SetFrictionY(bool _b) { m_FrictionY = _b; }

    float GetMaxSpeed() { return m_MaxSpeed; }

    void AddForce(Vec2 _Force) { m_Force += _Force; }
    void AddVelocity(Vec2 _Velocity) { m_Velocity += _Velocity; }

	void SetAutoMove(CObj* _Rigid) { m_Follower = _Rigid; }


    Vec2 GetForce() { return m_Force; }
    Vec2 GetAccel() { return m_Accel; }
    Vec2 GetVelocity() { return m_Velocity; }
    float GetMass() { return m_Mass; }


public:
    void MovePosition(Vec2 _Pos);

public:
    virtual void FinalTick() override;

public:
    CRigidBody();
    ~CRigidBody();
};

