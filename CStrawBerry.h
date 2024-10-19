#pragma once
#include "CObj.h"

class CPlayer;

class CStrawBerry
	: public CObj
{
protected:
	CPlayer*	m_Target;	// 먹혔을 때 플레이어를 따라다니기 위해 플레이어를 target으로써 저장함
	Vec2		m_TargetPos;

	Vec2		m_Offset;

	Vec2		m_OriPos;

	CAnimator*	m_Animator;
	CCollider*	m_Collider;

	float		m_MoveDuration;

	bool		m_Touched;
	bool		m_Collected;

	int			m_StID;
	int			m_OriRoom;

	bool		m_Ghost;


public:
	void SetOffset(Vec2 _Offset) { m_Offset = _Offset; }
	void SetOriPos(Vec2 _Pos) { m_OriPos = _Pos; }
	void SetStId(int _ID) { m_StID = _ID; }
	virtual void SetGhost(bool _b);


public:
	virtual void OnCollisionEnter(CCollider* _Col, CObj* _Other, CCollider* _OtherCol);

public:
	virtual bool Init() override;

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

