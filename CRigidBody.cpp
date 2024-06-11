#include "pch.h"
#include "CRigidBody.h"
#include "CObj.h"
#include "CTimeMgr.h"

Vec2 CRigidBody::m_GravityAccel = Vec2(0.f, 1200.f);
float CRigidBody::m_FrictionCoef = 300.f;

CRigidBody::CRigidBody()
	: m_Mass(1.f)
	, m_Gravity(true)
	, m_Ground(false)
	, m_Jump(false)
	, m_MaxSpeed(400.f)
	, m_GravityCoef(1.f)
	, m_GravityOriginalCoef(1.f)
	, m_GravityJumpCoef(0.3f)
	, m_JumpSpeed(300.f)
	, m_JumpEnd(false)
	, m_DashSpeed(540.f)
	, m_DashTime(0.5f)
	, m_DashAccTime(0.f)
	, m_Dash(false)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::Jump()
{
	if (m_Dash || !m_Ground)
		return;

	SetVelocity(Vec2(m_Velocity.x, -m_JumpSpeed));
	m_GravityCoef = m_GravityJumpCoef;
	m_Jump = true;
}

void CRigidBody::EndJump()
{
	m_GravityCoef = m_GravityOriginalCoef;
	m_Jump = false;
}

void CRigidBody::Dash(Vec2 _Dir)
{
	m_Dash = true;
	m_Gravity = false;
	if (!_Dir.IsZero())
	{
		SetVelocity(_Dir.Normalize() * m_DashSpeed);

	}
}

void CRigidBody::MovePosition(Vec2 _Pos)
{
	if (m_Dash)
		return;

	GetOwner()->SetPos(_Pos);
}


void CRigidBody::FinalTick()
{
	CObj* pOwner = GetOwner();

	m_Accel = m_Force / m_Mass;
	if (m_Gravity) m_Accel += m_GravityAccel * m_GravityCoef;
	
	//if (m_Force.IsZero())
	//{
	//	if (m_Velocity.Length() <= m_FrictionCoef * fDT)
	//		m_Velocity = Vec2(0.f, 0.f);
	//	else
	//		m_Velocity -= m_Velocity.Normalize() * m_FrictionCoef * fDT;
	//}

	m_Velocity += m_Accel * fDT;
	
	if (!m_Dash)
	{
		//if (m_Velocity.x > m_MaxSpeed) m_Velocity.x = m_MaxSpeed;
		//else if (m_Velocity.x < -m_MaxSpeed) m_Velocity.x = -m_MaxSpeed;

		if (m_Velocity.Length() > m_MaxSpeed)
		{
			m_Velocity.Normalize();
			m_Velocity *= m_MaxSpeed;
		}
	}
	else
	{
		m_DashAccTime += fDT;

		if (m_DashAccTime > m_DashTime)
		{
			m_DashAccTime = 0.f;
			m_Velocity.x = 0.f;
			//m_Velocity.y = 0.f;
			m_Dash = false;
			m_Gravity = true;
		}
	}

	if (m_Jump && fabs(m_Velocity.y) <= 1.f)
	{
		EndJump();
	}

	Vec2 vPos = pOwner->GetPos();
	vPos += m_Velocity * fDT;

	pOwner->SetPos(vPos);

	m_Force = Vec2(0.f, 0.f);
}
