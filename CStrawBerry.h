#pragma once
#include "CObj.h"

class CPlayer;

class CStrawBerry
	: public CObj
{
private:
	CPlayer*	m_Target;	// 먹혔을 때 플레이어를 따라다니기 위해 플레이어를 target으로써 저장함
	Vec2		m_TargetPos;

	Vec2		m_Offset;

	CAnimator*	m_Animator;

	float		m_MoveDuration;

	bool		m_Touched;
	bool		m_Collected;


public:
	void SetOffset(Vec2 _Offset) { m_Offset = _Offset; }

public:
	virtual void OnCollisionEnter(CCollider* _Col, CObj* _Other, CCollider* _OtherCol);

public:
	virtual void Tick() override;
	virtual void Render() override;


public:
	CStrawBerry();
	~CStrawBerry();
};

