#include "pch.h"
#include "CCollider.h"

#include "CObj.h"
#include "CDebugMgr.h"

#include "CEngine.h"

CCollider::CCollider()
	: m_OverlapCount(0)
{
}

CCollider::~CCollider()
{
}

void CCollider::BeginOverlap(CCollider* _Other)
{
	++m_OverlapCount;
}

void CCollider::Overlap(CCollider* _Other)
{
}

void CCollider::EndOverlap(CCollider* _Other)
{
	--m_OverlapCount;
}


void CCollider::FinalTick()
{
	m_FinalPos = GetOwner()->GetRenderPos() + m_Offset;
	
	if (m_OverlapCount > 0)
		Debug_Render(DEBUG_SHAPE::RECTANGLE, PEN_TYPE::RED, BRUSH_TYPE::HOLLOW, m_FinalPos, m_Scale);
	else
		Debug_Render(DEBUG_SHAPE::RECTANGLE, PEN_TYPE::GREEN, BRUSH_TYPE::HOLLOW, m_FinalPos, m_Scale);
}
