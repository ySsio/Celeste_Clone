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

	int			m_StID;

	bool		m_Ghost;


public:
	void SetOffset(Vec2 _Offset) { m_Offset = _Offset; }
	void SetStId(int _ID) { m_StID = _ID; }
	void SetGhost(bool _b);

public:
	virtual void OnCollisionEnter(CCollider* _Col, CObj* _Other, CCollider* _OtherCol);

public:
	virtual bool Save(FILE* _pFile) override;
	virtual void Load(FILE* _pFile) override;

public:
	virtual void Tick() override;
	virtual void Render() override;


public:
	CLONE(CStrawBerry)
	CStrawBerry();
	CStrawBerry(const CStrawBerry& _Other);
	~CStrawBerry();
};

