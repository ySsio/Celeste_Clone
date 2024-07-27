#include "pch.h"
#include "CObj.h"
#include "CEngine.h"

#include "CPlayer.h"

#include "CCollisionMgr.h"
#include "CTimeMgr.h"

CObj::CObj()
	: m_LayerType(LAYER_TYPE::END)
	, m_Room(-1)
	, m_Dead(false)
	, m_Moving(false)
	, m_AccTime(0.f)
	, m_Duration(0.f)
{
}

CObj::CObj(const CObj& _Other)
	: CBase(_Other)
	, m_LayerType(_Other.m_LayerType)
	, m_Pos(_Other.m_Pos)
	, m_Scale(_Other.m_Scale)
	, m_Room(-1)
	, m_Dead(false)
	, m_Moving(false)
	, m_AccTime(0.f)
	, m_Duration(0.f)
{
	for (auto& component : _Other.m_vecComponent)
	{
		CComponent* pClonedComponent = component->Clone();
		AddComponent(pClonedComponent);

		pClonedComponent->SetOwner(this);
	}
}

CObj::~CObj()
{
	Release_Vector(m_vecComponent);
}



void CObj::SetPosSmooth(float _Duration, Vec2 _Pos)
{
	if (m_Moving) return;

	m_Duration = _Duration;
	m_StartPos = m_Pos;
	m_TargetPos = _Pos;
	m_Moving = true;
}

Vec2 CObj::GetRenderPos()
{
	return RENDER_POS(GetPos());
}

void CObj::FinalTick()
{
	// SetPosSmooth
	if (m_Moving)
	{
		Vec2 Diff = m_TargetPos - m_StartPos;
		Vec2 Pos = m_Pos;

		m_AccTime += fDT;

		if (m_AccTime >= m_Duration)
		{
			m_AccTime = 0.f;
			m_Moving = false;
			SetPos(m_TargetPos);
		}
		else
		{
			Vec2 P1 = m_StartPos + Diff / 4.f;
			Vec2 P2 = m_StartPos + Diff * 3.f / 4.f;

			float ratio = m_AccTime / m_Duration;
			ratio = easeInOut(ratio);
			Pos = cubicBezier(m_StartPos, P1, P2, m_TargetPos, ratio);
			SetPos(Pos);
		}
	}

	// ÄÄÆ÷³ÍÆ® Final Tick
	for (auto comp : m_vecComponent)
	{
		comp->FinalTick();
		CCollider* pCol = dynamic_cast<CCollider*>(comp);
		if (pCol)
		{
			CCollisionMgr::Get()->RegisterCollider(pCol, m_LayerType);
		}
	}
}

void CObj::Render()
{
	Rectangle(BackDC
		, (int)(m_Pos.x - m_Scale.x / 2.f)
		, (int)(m_Pos.y - m_Scale.y / 2.f)
		, (int)(m_Pos.x + m_Scale.x / 2.f)
		, (int)(m_Pos.y + m_Scale.y / 2.f));

}


