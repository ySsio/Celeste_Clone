#include "pch.h"
#include "CRigidBody.h"
#include "CObj.h"
#include "CTimeMgr.h"

Vec2 CRigidBody::m_GravityAccel = Vec2(0.f, 2400.f);
float CRigidBody::m_FrictionCoef = 4800.f;
float CRigidBody::m_DashFrictionCoef = 1500.f;

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
	, m_DashCount(2)
	, m_DashMaxCount(2)
	, m_DashSpeed(1000.f)
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
	if (!CanDash() || _Dir.IsZero())
		return;

	if (m_Jump)
		EndJump();

	m_Dash = true;
	m_Gravity = false;
	--m_DashCount;

	SetVelocity(_Dir.Normalize() * m_DashSpeed);
}

void CRigidBody::MovePosition(Vec2 _Pos)
{
	GetOwner()->SetPos(_Pos);
}


void CRigidBody::FinalTick()
{
	CObj* pOwner = GetOwner();

	m_Accel = m_Force / m_Mass;
	if (m_Gravity) m_Accel += m_GravityAccel * m_GravityCoef;
	

	m_Velocity += m_Accel * fDT;
	
	// 평소 (대쉬 아닐때)
	if (!m_Dash)
	{
		// 1. 최대 속력을 넘지 않도록 조정
		if (m_Velocity.Length() > m_MaxSpeed)
		{
			m_Velocity.Normalize();
			m_Velocity *= m_MaxSpeed;
		}

		// 2. x 방향으로 마찰력을 줌
		if (m_Velocity.x != 0.f)
		{
			float dir = m_Velocity.x > 0.f ? 1.f : -1.f;

			m_Velocity.x = dir * (fabs(m_Velocity.x) - m_FrictionCoef * fDT);

			if (fabs(m_Velocity.x) < 5.f)
				m_Velocity.x = 0.f;
		}


	}
	// 대쉬 
	else
	{
		m_DashAccTime += fDT;

		// 대쉬 반대 방향으로 DashFrictionCoef 만큼 마찰력
		if (!m_Velocity.IsZero())
			m_Velocity -= m_Velocity.Normalized() * m_DashFrictionCoef * fDT;

		if (m_DashAccTime > m_DashTime)
		{
			m_DashAccTime = 0.f;
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
