#include "pch.h"
#include "CObj.h"
#include "CEngine.h"

#include "CPlayer.h"

#include "CCollisionMgr.h"

CObj::CObj()
	: m_Type(LAYER_TYPE::END)
	, m_Room(-1)
	, m_Dead(false)
{
}

CObj::CObj(const CObj& _Other)
	: CBase(_Other)
	, m_Type(_Other.m_Type)
	, m_Pos(_Other.m_Pos)
	, m_Scale(_Other.m_Scale)
	, m_Room(-1)
	, m_Dead(false)
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


Vec2 CObj::GetRenderPos()
{
	return RENDER_POS(GetPos());
}

void CObj::FinalTick()
{
	for (auto comp : m_vecComponent)
	{
		comp->FinalTick();
		CCollider* pCol = dynamic_cast<CCollider*>(comp);
		if (pCol)
		{
			CCollisionMgr::Get()->RegisterCollider(pCol, m_Type);
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


