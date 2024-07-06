#include "pch.h"
#include "CRigidBody.h"
#include "CObj.h"
#include "CTimeMgr.h"

Vec2 CRigidBody::m_GravityAccel = Vec2(0.f, 2400.f);

CRigidBody::CRigidBody()
	: m_Mass(1.f)
	, m_MaxSpeed(PLAYER_MAX_SPEED)
	, m_SpeedLimit(true)
	, m_FrictionCoef(FRICTION)
	, m_FrictionY(false)
	, m_Gravity(true)
	, m_Ground(false)
	, m_Jump(false)
	, m_GravityCoef(1.5f)
	, m_GravityOriginalCoef(1.5f)
	, m_GravityJumpCoef(1.f)
	, m_JumpSpeed(800.f)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::Jump()
{
	if (!m_Ground)
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

	// 1. 최대 속력을 넘지 않도록 조정
	if (m_SpeedLimit && m_Velocity.Length() > m_MaxSpeed)
	{
		m_Velocity.Normalize();
		m_Velocity *= m_MaxSpeed;
	}

	// 2. 마찰력
	// x축
	if (m_Velocity.x)
	{
		float dir = m_Velocity.Normalized().x;

		m_Velocity.x -= dir * m_FrictionCoef.x * fDT;

		if (fabs(m_Velocity.x) < 5.f)
			m_Velocity.x = 0.f;
	}

	// y축
	if (m_FrictionY && m_Velocity.y)
	{
		float dir = m_Velocity.Normalized().y;

		m_Velocity.y -= dir * m_FrictionCoef.y * fDT;

		if (fabs(m_Velocity.y) < 5.f)
			m_Velocity.y = 0.f;
	}
	


	// 점프 중에 속도가 0에 가까워지면 (최고점) 점프 종료
	if (m_Jump && fabs(m_Velocity.y) <= 5.f)
	{
		EndJump();
	}

	Vec2 vPos = pOwner->GetPos();
	vPos += m_Velocity * fDT;

	pOwner->SetPos(vPos);

	m_Force = Vec2(0.f, 0.f);
}
