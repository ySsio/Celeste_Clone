#include "pch.h"
#include "CPlatform.h"

#include "CTileMap.h"

#include "CTile.h"

#include "CAssetMgr.h"

CPlatform::CPlatform()
	: m_TileMap(nullptr)
{
	m_TileMap = AddComponent<CTileMap>();
}

CPlatform::CPlatform(const CPlatform& _Other)
	: CObj(_Other)
	, m_TileMap(nullptr)
{
	m_TileMap = GetComponent<CTileMap>();
}

CPlatform::~CPlatform()
{
}

void CPlatform::SetRowCol(UINT _Row, UINT _Col)
{
	if (m_TileMap) m_TileMap->SetRowCol(_Row, _Col);
}

bool CPlatform::Save(FILE* _pFile)
{
	// 1. ������Ʈ Ÿ���� ���ڿ��� ����
	wstring Type = L"Platform";
	int len = (int)Type.length();
	fwrite(&len, sizeof(int), 1, _pFile);
	fwrite(Type.c_str(), sizeof(wchar_t), len, _pFile);

	// 2. Room ���� ����
	int Room = GetRoom();
	fwrite(&Room, sizeof(int), 1, _pFile);

	// 3. ������ ����
	Vec2 VecBuff = GetPos();
	fwrite(&VecBuff, sizeof(Vec2), 1, _pFile);

	// 4. Ÿ�ϸ� RowCol ���� (Row, Col)
	UINT RowCnt = m_TileMap->GetRowCnt();
	fwrite(&RowCnt, sizeof(UINT), 1, _pFile);
	UINT ColCnt = m_TileMap->GetColCnt();
	fwrite(&ColCnt, sizeof(UINT), 1, _pFile);

	// 5. Ÿ�ϸ� UnitScale (Width, Height)
	UINT UWidth = m_TileMap->GetUnitWidth();
	fwrite(&UWidth, sizeof(UINT), 1, _pFile);
	UINT UHeight = m_TileMap->GetUnitHeight();
	fwrite(&UHeight, sizeof(UINT), 1, _pFile);

	// 6. Ÿ�ϸ��� Ÿ�� ���� ����
	// �� ĭ�� Ÿ�� �̸��� ������!! (Ÿ�� ��ü�� �ּ¸Ŵ������� �ε� �Ǿ� �ְ�, �̸������ε� ã�� �� �ִ� ����)

	const vector<CTile*>& Tileset = m_TileMap->GetTileset();

	for (UINT row = 0; row < RowCnt; ++row)
	{
		for (UINT col = 0; col < ColCnt; ++col)
		{
			wstring TileName = L"";

			// Ÿ�� ���� ���� L""�� ����
			if (Tileset[row * ColCnt + col])
				TileName = Tileset[row * ColCnt + col]->GetName();

			int len = (int)TileName.length();
			fwrite(&len, sizeof(int), 1, _pFile);
			fwrite(TileName.c_str(), sizeof(wchar_t), len, _pFile);
		}
	}

	// 6. �ݶ��̴� �߰� ���θ� ����
	bool HasCol = m_TileMap->HasCollider();
	fwrite(&HasCol, sizeof(bool), 1, _pFile);

	return true;
}

void CPlatform::Load(FILE* _pFile)
{
	// 1. ������Ʈ Ÿ���� ���� �� �Լ��� ȣ��� ��Ȳ
	// 2. Room ���� �ҷ���
	int Room = 0;
	fread(&Room, sizeof(int), 1, _pFile);
	SetRoom(Room);

	// 3. ������ �ҷ��ͼ� ����
	Vec2 VecBuff = Vec2();
	fread(&VecBuff, sizeof(Vec2), 1, _pFile);
	SetPos(VecBuff);

	// 4. RowCol �ҷ��ͼ� ����
	UINT RowCnt = 0;
	fread(&RowCnt, sizeof(UINT), 1, _pFile);
	UINT ColCnt = 0;
	fread(&ColCnt, sizeof(UINT), 1, _pFile);
	m_TileMap->SetRowCol(RowCnt, ColCnt);

	// 5. UnitScale �ҷ��ͼ� ����
	UINT UWidth = 0;
	fread(&UWidth, sizeof(UINT), 1, _pFile);
	UINT UHeight = 0;
	fread(&UHeight, sizeof(UINT), 1, _pFile);
	m_TileMap->SetUnitScale(UWidth, UHeight);

	// 6. Ÿ�ϸ��� Ÿ�� ���� �ҷ��ͼ� �� Ÿ�� ����
	for (UINT row = 0; row < RowCnt; ++row)
	{
		for (UINT col = 0; col < ColCnt; ++col)
		{
			int len = 0;
			fread(&len, sizeof(int), 1, _pFile);

			vector<wchar_t> szBuff(len + 1);
			fread(szBuff.data(), sizeof(wchar_t), len, _pFile);

			// Ÿ�� �̸��� ����
			wstring TileName = szBuff.data();

			// Ÿ�� �̸����� �ּ¸Ŵ������� Ÿ���� �ҷ��ͼ� ���� (row,col)�� ����
			CTile* pTile = CAssetMgr::Get()->FindAsset<CTile>(TileName);
			if (pTile)
				m_TileMap->SetTile(row, col, pTile);
		}
	}

	// 7. Collider ���θ� �о �ݶ��̴� ����
	bool hasCol = false;
	fread(&hasCol, sizeof(bool), 1, _pFile);

	if (hasCol)
		m_TileMap->AddCollider();
}

void CPlatform::Tick()
{
}

void CPlatform::Render()
{
	if (m_TileMap)
		m_TileMap->Render();
}
