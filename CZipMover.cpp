#include "pch.h"
#include "CZipMover.h"

#include "CEngine.h"
#include "CTimeMgr.h"
#include "CAssetMgr.h"

#include "CPlayer.h"

#include "CGameMgr.h"

#include "CCamera.h"

CZipMover::CZipMover()
	: m_Duration(1.f)
	, m_StartDuration(0.2f)
	, m_StopDuration(0.7f)
	, m_AccTime(0.f)
	, m_RigidBody(nullptr)
	, m_TileMap(nullptr)
	, m_Collider(nullptr)
	, m_Active(false)
	, m_Return(false)
{
	m_RigidBody = AddComponent<CRigidBody>();
	m_RigidBody->SetGravity(false);
	m_RigidBody->SetMaxSpeed(0.f);
	m_RigidBody->SetFrictionCoef(Vec2(0.f, 0.f));
	m_RigidBody->SetFrictionX(false);

	m_TileMap = AddComponent<CTileMap>();
	//m_TileMap->SetUnitScale(TILE_SCALE, TILE_SCALE);
	
	m_Collider = AddComponent<CCollider>();

	m_SpriteRenderer = AddComponent<CSpriteRenderer>();
}

CZipMover::~CZipMover()
{
}



void CZipMover::SetTile(UINT Row, UINT Col)
{
	// Row Col�� �������� �� ��� �⺻ �� �ڵ����� ����
	SetScale(Vec2(Col * TILE_SCALE, Row * TILE_SCALE));
	m_Collider->SetScale(Vec2(Col * TILE_SCALE, Row * TILE_SCALE));
	m_TileMap->SetRowCol(Row, Col);
	m_TileMap->SetOffset(-Vec2(Col * TILE_SCALE/2.f, Row * TILE_SCALE/2.f));
	m_SpriteRenderer->SetOffset(-Vec2(0.f, Row * TILE_SCALE/2.f - 30.f));

	// �ڵ����� Ÿ���� ä��
	for (UINT i = 0; i < Row; ++i)
	{
		for (UINT j = 0; j < Col; ++j)
		{
			if (i == 0)
			{
				if (j == 0)
				{
					m_TileMap->SetTile(i, j, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_zipmover_block_0_0"));
				}
				else if (j == Col -1)
				{
					m_TileMap->SetTile(i, j, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_zipmover_block_0_2"));
				}
				else
				{
					m_TileMap->SetTile(i, j, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_zipmover_block_0_1"));
				}
			}
			else if (i == Row-1)
			{
				if (j == 0)
				{
					m_TileMap->SetTile(i, j, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_zipmover_block_2_0"));
				}
				else if (j == Col -1)
				{
					m_TileMap->SetTile(i, j, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_zipmover_block_2_2"));
				}
				else
				{
					m_TileMap->SetTile(i, j, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_zipmover_block_2_1"));
				}
			}
			else
			{
				if (j == 0)
				{
					m_TileMap->SetTile(i, j, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_zipmover_block_1_0"));
				}
				else if (j == Col -1)
				{
					m_TileMap->SetTile(i, j, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_zipmover_block_1_2"));
				}
				else
				{
					m_TileMap->SetTile(i, j, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_zipmover_block_1_1"));
				}
			}

		}
	}
}

void CZipMover::Tick()
{
	m_SpriteRenderer->SetTexture(CAssetMgr::Get()->FindAsset<CTexture>(L"light01"));

	// ������������ ���������� ����
	if (m_Active)
	{
		m_AccTime += fDT;

		m_SpriteRenderer->SetTexture(CAssetMgr::Get()->FindAsset<CTexture>(L"light03"));

		if (m_AccTime >= m_StartDuration)
		{
			Vec2 vDiff = m_EndPos - m_StartPos;
			m_Dir = vDiff.Normalized();

			float Speed = max(vDiff.Length() / m_Duration, ZIP_MAX_SPEED);

			m_RigidBody->SetMaxSpeed(Speed);
			m_RigidBody->AddForce(m_Dir * Speed);

			// ��ġ�� �� ������ �Ѿ�� �� �������� ����
			if (vDiff.Length() < (GetPos() - m_StartPos).Length())
			{
				SetPos(m_EndPos);
				m_Return = true;
				m_Active = false;

				m_RigidBody->SetMaxSpeed(ZIP_RETURN_SPEED);
				m_RigidBody->SetVelocity(Vec2(0.f, 0.f));
				m_RigidBody->SetForce(Vec2(0.f, 0.f));

				m_AccTime = 0.f;
			}
		}
	}

	// ���������� ������������ õõ�� �ǵ��ƿ´�.
	if (m_Return)
	{
		m_AccTime += fDT;

		m_SpriteRenderer->SetTexture(CAssetMgr::Get()->FindAsset<CTexture>(L"light02"));

		if (m_AccTime >= m_StopDuration)
		{
			Vec2 vDiff = m_StartPos - m_EndPos;
			m_Dir = vDiff.Normalized();

			m_RigidBody->AddForce(m_Dir * ZIP_RETURN_SPEED);

			// ��ġ�� ���� ������ �Ѿ�� ������������ ����
			if (vDiff.Length() < (GetPos() - m_EndPos).Length())
			{
				SetPos(m_StartPos);
				m_Return = false;

				float Speed = max(vDiff.Length() / m_Duration, ZIP_MAX_SPEED);

				m_RigidBody->SetMaxSpeed(Speed);
				m_RigidBody->SetVelocity(Vec2(0.f, 0.f));
				m_RigidBody->SetForce(Vec2(0.f, 0.f));


				m_AccTime = 0.f;
			}
		}
	}

}

void CZipMover::Render()
{
	// Cog ������
	CTexture* pCog = CAssetMgr::Get()->FindAsset<CTexture>(L"cog");
	
	BLENDFUNCTION blend{};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	int Width = pCog->GetWidth();
	int Height = pCog->GetHeight();

	Vec2 StartRenderPos = CCamera::Get()->GetRenderPos(m_StartPos);
	Vec2 EndRenderPos = CCamera::Get()->GetRenderPos(m_EndPos);

	SELECT_PEN(BackDC, PEN_TYPE::RED_DASH);

	MoveToEx(BackDC, (int)StartRenderPos.x, (int)(StartRenderPos.y + 20.f), nullptr);
	LineTo(BackDC, (int)EndRenderPos.x, (int)(EndRenderPos.y + 20.f));

	MoveToEx(BackDC, (int)StartRenderPos.x, (int)(StartRenderPos.y - 20.f), nullptr);
	LineTo(BackDC, (int)EndRenderPos.x, (int)(EndRenderPos.y - 20.f));

	AlphaBlend(BackDC
		, (int)(StartRenderPos.x - Width/2.f)
		, (int)(StartRenderPos.y - Height /2.f)
		, Width, Height
		, pCog->GetDC()
		, 0, 0
		, Width, Height
		, blend);

	AlphaBlend(BackDC
		, (int)(EndRenderPos.x - Width/2.f)
		, (int)(EndRenderPos.y - Height /2.f)
		, Width, Height
		, pCog->GetDC()
		, 0, 0
		, Width, Height
		, blend);
	
	
	// Ÿ�ϸ� ������ (Block)
	if (m_TileMap)
		m_TileMap->Render();

	// ��ȣ�� �ؽ��� ������
	if (m_SpriteRenderer)
		m_SpriteRenderer->Render();

}