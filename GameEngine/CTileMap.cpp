#include "pch.h"
#include "CTileMap.h"
#include "CEngine.h"
#include "CObj.h"
#include "CTile.h"
#include "CTexture.h"
#include "CTimeMgr.h"

CTileMap::CTileMap()
	: m_UnitWidth((UINT)TILE_SCALE)
	, m_UnitHeight((UINT)TILE_SCALE)
	, m_RowCnt(0)
	, m_ColCnt(0)
	, m_HasCol(false)
	, m_Crumble(false)
	, m_AccTime(0.f)
	, m_Duration(0.04f)
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
	for (UINT Row = 0; Row < m_RowCnt; ++Row)
	{
		for (UINT Col = 0; Col < m_ColCnt; ++Col)
		{
			if (!m_vecTile[Row * m_ColCnt + Col] || !m_vecTile[Row * m_ColCnt + Col]->HasCollider())
			{
				continue;
			}

			Vec2 vTilePos = Vec2((float)Col * m_UnitWidth, (float)Row * m_UnitHeight) + m_Offset;

			const tColInfo& Info = m_vecTile[Row * m_ColCnt + Col]->GetColInfo();

			CCollider* pCol = GetOwner()->AddComponent<CCollider>();
			pCol->SetOffset(vTilePos + Vec2(Info.Offset.x * m_UnitWidth, Info.Offset.y * m_UnitHeight));
			pCol->SetScale(Vec2(Info.Scale.x * m_UnitWidth, Info.Scale.y * m_UnitHeight));

			m_mapCol.emplace(pCol, Vec2((float)Row, (float)Col));
		}
	}

	SetCollider(true);
}

void CTileMap::FinalTick()
{
}

void CTileMap::Render()
{
	Vec2 vRenderPos = GetOwner()->GetRenderPos();
	vRenderPos += m_Offset;

	if (m_Crumble)
	{
		m_AccTime += fDT;
	}

	for (UINT Row = 0; Row < m_RowCnt; ++Row)
	{
		for (UINT Col = 0; Col < m_ColCnt; ++Col)
		{
			if (!m_vecTile[Row * m_ColCnt + Col])
				continue;

			Vec2 vTilePos = vRenderPos;
			vTilePos.y += Row * m_UnitHeight;
			vTilePos.x += Col * m_UnitWidth;

			CTexture* pTex = m_vecTile[Row * m_ColCnt + Col]->GetTex();

			if (m_Crumble)
			{
				// Duration마다 랜덤한 오프셋 설정
				if (m_AccTime >= m_Duration)
				{
					static int Len = (int)(TILE_SCALE / 8.f);

					// 랜덤한 오프셋 부여
					m_CrumbleOffsets[Row * m_ColCnt + Col] = Vec2(rand() % (Len * 2) - Len, rand() % (Len * 2) - Len);
				}

				vTilePos += m_CrumbleOffsets[Row * m_ColCnt + Col];
			}

			BLENDFUNCTION blend{};
			blend.BlendOp = AC_SRC_OVER;
			blend.BlendFlags = 0;
			blend.SourceConstantAlpha = 255;
			blend.AlphaFormat = AC_SRC_ALPHA;

			AlphaBlend(BackDC
				, (int)vTilePos.x
				, (int)vTilePos.y
				, m_UnitWidth
				, m_UnitHeight
				, pTex->GetDC()
				, (int)m_vecTile[Row * m_ColCnt + Col]->GetLT().x
				, (int)m_vecTile[Row * m_ColCnt + Col]->GetLT().y
				, (int)m_vecTile[Row * m_ColCnt + Col]->GetScale().x
				, (int)m_vecTile[Row * m_ColCnt + Col]->GetScale().y
				, blend);

		}
	}

	if (m_Crumble)
	{
		if (m_AccTime >= m_Duration)
			m_AccTime -= m_Duration;
	}
}
