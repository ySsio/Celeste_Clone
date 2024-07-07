#pragma once
#include "CObj.h"

class CPlayer;

class CStrawBerry
	: public CObj
{
private:
	CPlayer*	m_Target;	// ������ �� �÷��̾ ����ٴϱ� ���� �÷��̾ target���ν� ������
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

