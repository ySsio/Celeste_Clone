#include "pch.h"
#include "CCrumbleBlock.h"

#include "CAssetMgr.h"
#include "CTimeMgr.h"

#include "CPlayer.h"

CCrumbleBlock::CCrumbleBlock()
	: m_BlockTile(nullptr)
	, m_OutlineTile(nullptr)
	, m_Collider(nullptr)
	, m_AccTime(0.f)
	, m_Duration(1.f)
	, m_ResetDuration(2.5f)
	, m_Touch(false)
	, m_Active(true)
{
	m_BlockTile = AddComponent<CTileMap>();
	m_OutlineTile = AddComponent<CTileMap>();
	m_Collider = AddComponent<CCollider>();
}

CCrumbleBlock::CCrumbleBlock(const CCrumbleBlock& _Other)
	: m_BlockTile(nullptr)
	, m_OutlineTile(nullptr)
	, m_Collider(nullptr)
	, m_AccTime(0.f)
	, m_Duration(1.f)
	, m_ResetDuration(2.5f)
	, m_Touch(false)
	, m_Active(true)
{
	const auto& TileMaps = GetComponents<CTileMap>();
	m_BlockTile = TileMaps[0];
	m_OutlineTile = TileMaps[1];
	m_Collider = GetComponent<CCollider>();
}

CCrumbleBlock::~CCrumbleBlock()
{
}

void CCrumbleBlock::SetTile(UINT Col)
{
	// Row Col�� �������� �� ��� �⺻ �� �ڵ����� ����
	SetScale(Vec2(Col * TILE_SCALE, TILE_SCALE));
	m_Collider->SetScale(Vec2(Col * TILE_SCALE, TILE_SCALE));
	m_BlockTile->SetRowCol(1, Col);
	m_BlockTile->SetOffset(-Vec2(Col * TILE_SCALE / 2.f, TILE_SCALE / 2.f));
	m_OutlineTile->SetRowCol(1, Col);
	m_OutlineTile->SetOffset(-Vec2(Col * TILE_SCALE / 2.f, TILE_SCALE / 2.f) + Vec2(0.f, TILE_SCALE / 8.f));

	// �ڵ����� Ÿ���� ä��
	for (UINT j = 0; j < Col; ++j)
	{
		m_BlockTile->SetTile(0, j, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_CrumbleBlock_0_" + std::to_wstring(Col % 4)));

		if (Col==1)
			m_OutlineTile->SetTile(0, j, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_CrumbleOutline_0_" + std::to_wstring(3)));
		else
		{
			if (j==0)
				m_OutlineTile->SetTile(0, j, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_CrumbleOutline_0_" + std::to_wstring(0)));
			else if (j==Col-1)
				m_OutlineTile->SetTile(0, j, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_CrumbleOutline_0_" + std::to_wstring(2)));
			else
				m_OutlineTile->SetTile(0, j, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_CrumbleOutline_0_" + std::to_wstring(1)));
		}
	}
}

void CCrumbleBlock::Crumble(bool _b)
{
	m_BlockTile->Crumble(_b);
}

void CCrumbleBlock::Active()
{
	m_Active = false;
	m_Touch = false;
	m_Collider->SetActive(false);
	m_AccTime = 0.f;
	Crumble(false);
}

void CCrumbleBlock::Reset()
{
	m_Active = true;
	m_Collider->SetActive(true);
	m_AccTime = 0.f;
}

bool CCrumbleBlock::Save(FILE* _pFile)
{
	// 1. ������Ʈ ������ ���ڿ��� ����
	wstring Type = L"CrumbleBlock";
	int len = (int)Type.length();
	fwrite(&len, sizeof(int), 1, _pFile);
	fwrite(Type.c_str(), sizeof(wchar_t), len, _pFile);

	// 2. Room ���� ����
	int Room = GetRoom();
	fwrite(&Room, sizeof(int), 1, _pFile);

	// 3. ������ ����
	Vec2 VecBuff = GetPos();
	fwrite(&VecBuff, sizeof(Vec2), 1, _pFile);

	// 4. Col ����
	int Col = m_BlockTile->GetColCnt();
	fwrite(&Col, sizeof(int), 1, _pFile);

	return true;
}

void CCrumbleBlock::Load(FILE* _pFile)
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

	// 4. Col �޾ƿͼ� ����
	int Col = 0;
	fread(&Col, sizeof(int), 1, _pFile);
	SetTile(Col);
}


void CCrumbleBlock::Tick()
{
	// �ǵ���� �� Ʈ���� �۵� -> player collision���� ����
	if (m_Touch)
	{
		m_AccTime += fDT;

		if (m_AccTime >= m_Duration)
		{
			Active();
		}
	}

	// �ð��� ���� ��Ȱ��ȭ��
	if (!m_Active)
	{
		m_AccTime += fDT;

		if (m_AccTime >= m_ResetDuration)
		{
			Reset();
		}
	}
}

void CCrumbleBlock::Render()
{
	if (m_Active)
		m_BlockTile->Render();
	else
		m_OutlineTile->Render();
}
