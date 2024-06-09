#include "pch.h"
#include "CRigidBody.h"
#include "CObj.h"
#include "CTimeMgr.h"

Vec2 CRigidBody::m_GravityAccel = Vec2(0.f, 700.f);

CRigidBody::CRigidBody()
	: m_Mass(1.f)
	, m_JumpSpeed(500.f)
	, m_Gravity(true)
	, m_Ground(false)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::Jump()
{
	SetVelocity(Vec2(vVelocity.x, -m_JumpSpeed));
}

void CRigidBody::FinalTick()
{
	CObj* pOwner = GetOwner();

	m_Accel = m_Force / m_Mass;
	if (m_Gravity) m_Accel += m_GravityAccel;

	vVelocity += m_Accel * fDT;

	Vec2 vPos = pOwner->GetPos();
	vPos += vVelocity * fDT;

	pOwner->SetPos(vPos);

	m_Force = Vec2(0.f, 0.f);
}
