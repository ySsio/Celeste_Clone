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

void CCollisionMgr::ClearCollider()
{
	for (auto& Layer : m_arrCollider)
	{
		Layer.clear();
	}
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

bool CCollisionMgr::CollisionCheck(CCollider* _Col1, CCollider* _Col2)
{
	// Active 하지 않은 녀석들에 대해서는 감지를 하지 않음
	if (!_Col1->IsActive() || !_Col2->IsActive())
		return false;

	Vec2 vPos1 = _Col1->GetFinalPos();
	Vec2 vPos2 = _Col2->GetFinalPos();
	Vec2 vScale1 = _Col1->GetScale();
	Vec2 vScale2 = _Col2->GetScale();

	if (fabs(vPos1.x - vPos2.x) <= (vScale1.x + vScale2.x) / 2.f
		&& fabs(vPos1.y - vPos2.y) <= (vScale1.y + vScale2.y) / 2.f)
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
		for (UINT col = 0; col < (UINT)LAYER_TYPE::END - row; ++col)
		{
			if (!(m_Matrix[row] & (1 << col)))
				continue;

			CollisionLayerCheck(row, col);
		}
	}


	// 콜라이더 모두 해제
	ClearCollider();
}
