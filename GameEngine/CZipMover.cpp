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
	, m_SoundA(false)
	, m_SoundB(false)
	, m_SoundC(false)
	, m_SoundD(false)
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
	m_SpriteRenderer->SetTex(CAssetMgr::Get()->FindAsset<CTexture>(L"light01"));
}

CZipMover::CZipMover(const CZipMover& _Other)
	: CObj(_Other)
	, m_Duration(1.f)
	, m_StartDuration(0.2f)
	, m_StopDuration(0.7f)
	, m_AccTime(0.f)
	, m_RigidBody(nullptr)
	, m_TileMap(nullptr)
	, m_Collider(nullptr)
	, m_Active(false)
	, m_Return(false)
	, m_SoundA(false)
	, m_SoundB(false)
	, m_SoundC(false)
	, m_SoundD(false)
{
	m_RigidBody = GetComponent<CRigidBody>();
	m_TileMap = GetComponent<CTileMap>();
	m_Collider = GetComponent<CCollider>();
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

bool CZipMover::Init()
{
	SetPos(m_StartPos);
	m_AccTime = 0.f;
	m_Active = false;
	m_Return = false;
	m_Reset = false;
	m_RigidBody->SetVelocity(Vec2(0.f, 0.f));

	m_SoundA = false;
	m_SoundB = false;
	m_SoundC = false;
	m_SoundD = false;

	CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\obj\\zipmover\\game_01_zipmover_a_touch_01.wav")->Stop();
	CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\obj\\zipmover\\game_01_zipmover_b_impact_01.wav")->Stop();
	CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\obj\\zipmover\\game_01_zipmover_c_return_01.wav")->Stop();
	CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\obj\\zipmover\\game_01_zipmover_d_reset_01.wav")->Stop();

	return true;
}

bool CZipMover::Save(FILE* _pFile)
{
	// 1. ������Ʈ ������ ���ڿ��� ����
	wstring Type = L"ZipMover";
	int len = (int)Type.length();
	fwrite(&len, sizeof(int), 1, _pFile);
	fwrite(Type.c_str(), sizeof(wchar_t), len, _pFile);

	// 2. Room ���� ����
	int Room = GetRoom();
	fwrite(&Room, sizeof(int), 1, _pFile);

	// 3. ������ ����
	Vec2 VecBuff = GetPos();
	fwrite(&VecBuff, sizeof(Vec2), 1, _pFile);

	// 4. StartPos ����
	fwrite(&m_StartPos, sizeof(Vec2), 1, _pFile);

	// 5. EndPos ����
	fwrite(&m_EndPos, sizeof(Vec2), 1, _pFile);

	// 6. RowCol ����
	VecBuff = Vec2((float)m_TileMap->GetRowCnt(), (float)m_TileMap->GetColCnt());
	fwrite(&VecBuff, sizeof(Vec2), 1, _pFile);

	return true;
}

void CZipMover::Load(FILE* _pFile)
{
	// 1. ������Ʈ ������ ���� �� �Լ��� ȣ��� ��Ȳ
	// 2. Room ���� �ҷ���
	int Room = 0;
	fread(&Room, sizeof(int), 1, _pFile);
	SetRoom(Room);

	// 3. �������� �޾ƿͼ� ����
	Vec2 VecBuff = Vec2();
	fread(&VecBuff, sizeof(Vec2), 1, _pFile);
	SetPos(VecBuff);

	// 4. StartPos�� �޾ƿͼ� ����
	fread(&m_StartPos, sizeof(Vec2), 1, _pFile);

	// 5. EndPos �޾ƿͼ� ����
	fread(&m_EndPos, sizeof(Vec2), 1, _pFile);

	// 6. RowCol �޾ƿͼ� ����
	fread(&VecBuff, sizeof(Vec2), 1, _pFile);
	SetTile((UINT)VecBuff.x, (UINT)VecBuff.y);
}

void CZipMover::Tick()
{
	m_SpriteRenderer->SetTex(CAssetMgr::Get()->FindAsset<CTexture>(L"light01"));

	// ������������ ���������� ����
	if (m_Active)
	{
		m_AccTime += fDT;

		m_SpriteRenderer->SetTex(CAssetMgr::Get()->FindAsset<CTexture>(L"light03"));

		if (m_AccTime >= m_StartDuration)
		{
			if (!m_SoundA && GetRoom() == CGameMgr::Get()->GetPlayer()->GetRoom())
			{
				// Sound ���
				CSound* pSound = CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\obj\\zipmover\\game_01_zipmover_a_touch_01.wav");
				pSound->Play();

				m_SoundA = true;
			}

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
		if (!m_SoundB && GetRoom() == CGameMgr::Get()->GetPlayer()->GetRoom())
		{
			// Sound ���
			CSound* pSound = CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\obj\\zipmover\\game_01_zipmover_b_impact_01.wav");
			pSound->Play();

			m_SoundB = true;
		}

		m_AccTime += fDT;

		m_SpriteRenderer->SetTex(CAssetMgr::Get()->FindAsset<CTexture>(L"light02"));

		if (m_AccTime >= m_StopDuration)
		{
			if (!m_SoundC && GetRoom() == CGameMgr::Get()->GetPlayer()->GetRoom())
			{
				// Sound ���
				CSound* pSound = CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\obj\\zipmover\\game_01_zipmover_c_return_01.wav");
				pSound->Play();

				m_SoundC = true;
			}


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

				// �� �� �۵��� �� �޽� ���¿� ����
				m_Reset = true;

				m_AccTime = 0.f;
			}
		}
	}

	if (m_Reset)
	{
		m_AccTime += fDT;

		if (!m_SoundD && GetRoom() == CGameMgr::Get()->GetPlayer()->GetRoom())
		{
			// Sound ���
			CSound* pSound = CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\obj\\zipmover\\game_01_zipmover_d_reset_01.wav");
			pSound->Play();

			m_SoundD = true;
		}

		if (m_AccTime >= m_StopDuration)
		{
			Init();
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