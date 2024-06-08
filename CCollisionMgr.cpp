#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CObj.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	: m_Matrix{}
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::RegisterCollisionLayer(LAYER_TYPE _Type1, LAYER_TYPE _Type2, bool _b)
{
	if ((UINT)_Type1 > (UINT)_Type2)
		std::swap(_Type1, _Type2);

	if (_b) 
		m_Matrix[(UINT)_Type1] |= (1 << (UINT)_Type2);
	else
		m_Matrix[(UINT)_Type1] &= ~(1 << (UINT)_Type2);
}

void CCollisionMgr::CollisionLayerCheck(UINT _Layer1, UINT _Layer2)
{
	const vector<CCollider*>& Group1 = m_arrCollider[_Layer1];
	const vector<CCollider*>& Group2 = m_arrCollider[_Layer2];
	
	for (auto Col1 : Group1)
	{
		for (auto Col2 : Group2)
		{
			COLLISION_ID colID{};
			colID.ID1 = Col1->GetID();
			colID.ID2 = Col2->GetID();

			unordered_map<DWORD_PTR, bool>::iterator iter = m_ColInfo.find(colID.ID);

			if (iter == m_ColInfo.end())
			{
				m_ColInfo.emplace(colID.ID, false);
				iter = m_ColInfo.find(colID.ID);
			}

			bool IsDead = Col1->GetOwner()->IsDead() || Col2->GetOwner()->IsDead();

			// 이번 프레임에 충돌 발생
			if (!IsDead && CollisionCheck(Col1, Col2))
			{
				// 이전 프레임에도 충돌한 상태
				if (iter->second)
				{
					Col1->Overlap(Col2);
					Col2->Overlap(Col1);
				}
				// 이전 프레임에는 충돌 x
				else
				{
					Col1->BeginOverlap(Col2);
					Col2->BeginOverlap(Col1);
					iter->second = true;
				}
			}
			// 이번 프레임에 충돌 x
			else
			{
				// 이전 프레임에 충돌한 상태
				if (iter->second)
				{
					Col1->EndOverlap(Col2);
					Col2->EndOverlap(Col1);
					iter->second = false;
				}
			}
		}
	}
}

bool CCollisionMgr::CollisionCheck(CCollider* _Obj1, CCollider* _Obj2)
{
	Vec2 vPos1 = _Obj1->GetFianlPos();
	Vec2 vPos2 = _Obj2->GetFianlPos();
	Vec2 vScale1 = _Obj1->GetScale();
	Vec2 vScale2 = _Obj2->GetScale();

	if (vPos1.x - vScale1.x < vPos2.x + vScale2.x
		&& vPos2.x - vScale2.x < vPos1.x + vScale1.x)
	{
		return true;
	}

	return false;
}

void CCollisionMgr::Init()
{
}

void CCollisionMgr::Tick()
{
	for (UINT row = 0; row < (UINT)LAYER_TYPE::END; ++row)
	{
		for (UINT col = 0; col <= row; ++col)
		{
			if (!(m_Matrix[row] & (1 << col)))
				continue;

			CollisionLayerCheck(row, col);
		}
	}


	// 콜라이더 모두 해제
	for (auto& vecLayer : m_arrCollider)
	{
		vecLayer.clear();
	}
}
