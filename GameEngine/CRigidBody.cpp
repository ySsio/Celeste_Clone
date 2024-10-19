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
	, m_FrictionX(true)
	, m_FrictionY(false)
	, m_Gravity(true)
	, m_GravityCoef(GRAVITY_COEF)
	, m_GravityOriginalCoef(GRAVITY_COEF)
	, m_GravityJumpCoef(GRAVITY_COEF_JUMP)
	, m_JumpSpeed(PLAYER_JUMP_SPEED)
	, m_Follower(nullptr)
{
}

CRigidBody::~CRigidBody()
{
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

	// 1. �ִ� �ӷ��� ���� �ʵ��� ���� - x�� y�� ����..
	if (m_SpeedLimit)
	{
		if (fabs(m_Velocity.x) > m_MaxSpeed)
			m_Velocity.x = m_Velocity.x > 0.f ? m_MaxSpeed : -m_MaxSpeed;
		
		if (fabs(m_Velocity.y) > m_MaxSpeed)
			m_Velocity.y = m_Velocity.y > 0.f ? m_MaxSpeed : -m_MaxSpeed;
	}

	// 2. ������
	// x��
	if (m_FrictionX && m_Velocity.x)
	{
		float dir = m_Velocity.Normalized().x;

		m_Velocity.x -= dir * m_FrictionCoef.x * fDT;

		if (fabs(m_Velocity.x) < 5.f)
			m_Velocity.x = 0.f;
	}

	// y��
	if (m_FrictionY && m_Velocity.y)
	{
		float dir = m_Velocity.Normalized().y;

		m_Velocity.y -= dir * m_FrictionCoef.y * fDT;

		if (fabs(m_Velocity.y) < 5.f)
			m_Velocity.y = 0.f;
	}
	

	Vec2 vPos = pOwner->GetPos();
	Vec2 vDiff = m_Velocity * fDT;

	if (m_Follower)
	{
		m_Follower->SetPos(m_Follower->GetPos() + vDiff);
		

		// �̰� �ּ� �ɸ� Follower�� �з��� ���� �����ѵ� ����� ���� ���������� �ݶ��̴��� �������� ���� �߻�
		// �̰� �ּ� �Ȱɸ� Follower�� ����� ���� �����ѵ� �з����ٰ� ������ �� Follower Rigidbody���� �̵��� �Ÿ��� �־ ƨ�ܳ��� ������ ���� �߻�
		vector<CCollider*> cols = m_Follower->GetComponents<CCollider>();
		for (auto col : cols)
		{
			col->FinalTick();
		}
	}

	pOwner->SetPos(vPos + vDiff);

	m_Force = Vec2(0.f, 0.f);
}
