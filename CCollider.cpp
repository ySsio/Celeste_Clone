#include "pch.h"
#include "CCollider.h"

#include "CObj.h"
#include "CDebugMgr.h"

#include "CEngine.h"

CCollider::CCollider()
	: m_Trigger(false)
	, m_OverlapCount(0)
{
}

CCollider::~CCollider()
{
}

void CCollider::BeginOverlap(CCollider* _Other)
{
	++m_OverlapCount;
	GetOwner()->OnCollisionEnter(this, _Other->GetOwner(), _Other);
}

void CCollider::Overlap(CCollider* _Other)
{
	GetOwner()->OnCollision(this, _Other->GetOwner(), _Other);
}

void CCollider::EndOverlap(CCollider* _Other)
{
	--m_OverlapCount;
	GetOwner()->OnCollisionExit(this, _Other->GetOwner(), _Other);
}


void CCollider::FinalTick()
{
	m_FinalPos = GetOwner()->GetPos() + m_MaxDistance;

	Vec2 vRenderPos = GetOwner()->GetRenderPos() + m_MaxDistance;
	
	if (m_OverlapCount > 0)
		Debug_Render(DEBUG_SHAPE::RECTANGLE, PEN_TYPE::RED, BRUSH_TYPE::HOLLOW, vRenderPos, m_Scale);
	else
		Debug_Render(DEBUG_SHAPE::RECTANGLE, PEN_TYPE::GREEN, BRUSH_TYPE::HOLLOW, vRenderPos, m_Scale);
}
