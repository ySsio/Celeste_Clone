#include "pch.h"
#include "CRigidBody.h"
#include "CObj.h"
#include "CTimeMgr.h"

Vec2 CRigidBody::m_GravityAccel = Vec2(0.f, 2400.f);
float CRigidBody::m_FrictionCoef = 600.f;

CRigidBody::CRigidBody()
	: m_Mass(1.f)
	, m_Gravity(true)
	, m_Ground(false)
	, m_Jump(false)
	, m_MaxSpeed(800.f)
	, m_GravityCoef(2.f)
	, m_GravityOriginalCoef(2.f)
	, m_GravityJumpCoef(0.6f)
	, m_JumpSpeed(600.f)
	, m_DashCount(1)
	, m_DashMaxCount(1)
	, m_DashSpeed(860.f)
	, m_DashTime(0.3f)
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
	assert(m_Jump);

	SetVelocity(Vec2(m_Velocity.x, 0.f));
	m_GravityCoef = m_GravityOriginalCoef;
	m_Jump = false;
}

void CRigidBody::Dash(Vec2 _Dir)
{
	if (!CanDash())
		return;

	m_Dash = true;
	m_Gravity = false;
	--m_DashCount;
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
	

	m_Velocity += m_Accel * fDT;
	
	if (!m_Dash)
	{
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

	if (m_Jump && fabs(m_Velocity.y) <= 5.f)
	{
		EndJump();
	}

	Vec2 vPos = pOwner->GetPos();
	vPos += m_Velocity * fDT;

	pOwner->SetPos(vPos);

	m_Force = Vec2(0.f, 0.f);
}
