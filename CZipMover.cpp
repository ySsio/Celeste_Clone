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
	m_TileMap->SetRowCol(3, 3);
	m_TileMap->SetUnitScale(40, 40);
	m_TileMap->SetOffset(Vec2(-60.f, -60.f));

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			m_TileMap->SetTile(i, j, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_zipmover_block_" + std::to_wstring(i) + L"_" + std::to_wstring(j)));
		}
	}


	m_Collider = AddComponent<CCollider>();
	m_Collider->SetScale(Vec2(120.f, 120.f));

}

CZipMover::~CZipMover()
{
}


void CZipMover::Tick()
{
	// ������������ ���������� ����
	if (m_Active)
	{
		m_AccTime += fDT;

		if (m_AccTime >= m_StartDuration)
		{
			Vec2 vDiff = m_EndPos - m_StartPos;
			m_Dir = vDiff.Normalized();

			float Speed = max(vDiff.Length() / m_Duration, ZIP_MAX_SPEED);

			CRigidBody* pPlayerRigid = CGameMgr::Get()->GetPlayer()->GetRigidBody();

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

		if (m_AccTime >= m_StopDuration)
		{
			Vec2 vDiff = m_StartPos - m_EndPos;
			m_Dir = vDiff.Normalized();

			CRigidBody* pPlayerRigid = CGameMgr::Get()->GetPlayer()->GetRigidBody();

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

	MoveToEx(BackDC, StartRenderPos.x, StartRenderPos.y + 20.f, nullptr);
	LineTo(BackDC, EndRenderPos.x, EndRenderPos.y + 20.f);

	MoveToEx(BackDC, StartRenderPos.x, StartRenderPos.y - 20.f, nullptr);
	LineTo(BackDC, EndRenderPos.x, EndRenderPos.y - 20.f);

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

}