#include "pch.h"
#include "CTileMap.h"
#include "CEngine.h"
#include "CObj.h"
#include "CTile.h"
#include "CTexture.h"

CTileMap::CTileMap()
	: m_UnitWidth(0)
	, m_UnitHeight(0)
	, m_RowCnt(0)
	, m_ColCnt(0)
{

}

CTileMap::~CTileMap()
{
}

void CTileMap::SetTile(UINT _Row, UINT _Col, CTile* _Tile)
{
	assert(_Row <= m_RowCnt && _Col <= m_ColCnt);

	m_vecTile[_Row * m_ColCnt + _Col] = _Tile;
}

Vec2 CTileMap::FindCollider(CCollider* _Col)
{
	auto iter = m_mapCol.find(_Col);

	assert(iter != m_mapCol.end());

	return iter->second;
}

bool CTileMap::IsTileDanger(CCollider* _Col)
{
	Vec2 RowCol = FindCollider(_Col);
 	return m_vecTile[(UINT)(RowCol.x * m_ColCnt + RowCol.y)]->IsDanger();
}

void CTileMap::AddCollider()
{
	Vec2 vRenderPos = GetOwner()->GetRenderPos();
	for (UINT Row = 0; Row < m_RowCnt; ++Row)
	{
		for (UINT Col = 0; Col < m_ColCnt; ++Col)
		{
			if (!m_vecTile[Row * m_ColCnt + Col] || !m_vecTile[Row * m_ColCnt + Col]->HasCollider())
			{
				continue;
			}

			Vec2 vTilePos = vRenderPos;
			vTilePos.y += Row * m_UnitHeight;
			vTilePos.x += Col * m_UnitWidth;

			const tColInfo& Info = m_vecTile[Row * m_ColCnt + Col]->GetColInfo();

			CCollider* pCol = GetOwner()->AddComponent<CCollider>();
			pCol->SetOffset(Vec2((float)(Col * m_UnitWidth), (float)(Row * m_UnitHeight)) + Vec2(Info.Offset.x * m_UnitWidth, Info.Offset.y * m_UnitHeight));
			pCol->SetScale(Vec2(Info.Scale.x * m_UnitWidth, Info.Scale.y * m_UnitHeight));

			m_mapCol.emplace(pCol, Vec2((float)Row, (float)Col));
		}
	}
}

void CTileMap::FinalTick()
{
}

void CTileMap::Render()
{
	Vec2 vRenderPos = GetOwner()->GetRenderPos();
	for (UINT Row = 0; Row < m_RowCnt; ++Row)
	{
		for (UINT Col = 0; Col < m_ColCnt; ++Col)
		{
			if (!m_vecTile[Row * m_ColCnt + Col])
				continue;

			Vec2 vTilePos = vRenderPos;
			vTilePos.y += Row * m_UnitHeight;
			vTilePos.x += Col * m_UnitWidth;

			CTexture* pTex = m_vecTile[Row * m_ColCnt + Col]->GetTexture();

			StretchBlt(BackDC
				, (int)vTilePos.x
				, (int)vTilePos.y
				, m_UnitWidth
				, m_UnitHeight
				, pTex->GetDC()
				, (int)m_vecTile[Row * m_ColCnt + Col]->GetLT().x
				, (int)m_vecTile[Row * m_ColCnt + Col]->GetLT().y
				, (int)m_vecTile[Row * m_ColCnt + Col]->GetScale().x
				, (int)m_vecTile[Row * m_ColCnt + Col]->GetScale().y
				, SRCCOPY);

		}
	}
}
