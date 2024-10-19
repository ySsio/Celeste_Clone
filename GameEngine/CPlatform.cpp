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
	// 1. 오브젝트 타입을 문자열로 저장
	wstring Type = L"Platform";
	int len = (int)Type.length();
	fwrite(&len, sizeof(int), 1, _pFile);
	fwrite(Type.c_str(), sizeof(wchar_t), len, _pFile);

	// 2. Room 정보 저장
	int Room = GetRoom();
	fwrite(&Room, sizeof(int), 1, _pFile);

	// 3. 포지션 저장
	Vec2 VecBuff = GetPos();
	fwrite(&VecBuff, sizeof(Vec2), 1, _pFile);

	// 4. 타일맵 RowCol 저장 (Row, Col)
	UINT RowCnt = m_TileMap->GetRowCnt();
	fwrite(&RowCnt, sizeof(UINT), 1, _pFile);
	UINT ColCnt = m_TileMap->GetColCnt();
	fwrite(&ColCnt, sizeof(UINT), 1, _pFile);

	// 5. 타일맵 UnitScale (Width, Height)
	UINT UWidth = m_TileMap->GetUnitWidth();
	fwrite(&UWidth, sizeof(UINT), 1, _pFile);
	UINT UHeight = m_TileMap->GetUnitHeight();
	fwrite(&UHeight, sizeof(UINT), 1, _pFile);

	// 6. 타일맵의 타일 정보 저장
	// 각 칸의 타일 이름을 저장함!! (타일 자체는 애셋매니저에서 로드 되어 있고, 이름만으로도 찾을 수 있는 구조)

	const vector<CTile*>& Tileset = m_TileMap->GetTileset();

	for (UINT row = 0; row < RowCnt; ++row)
	{
		for (UINT col = 0; col < ColCnt; ++col)
		{
			wstring TileName = L"";

			// 타일 없는 곳은 L""로 저장
			if (Tileset[row * ColCnt + col])
				TileName = Tileset[row * ColCnt + col]->GetName();

			int len = (int)TileName.length();
			fwrite(&len, sizeof(int), 1, _pFile);
			fwrite(TileName.c_str(), sizeof(wchar_t), len, _pFile);
		}
	}

	// 6. 콜라이더 추가 여부를 저장
	bool HasCol = m_TileMap->HasCollider();
	fwrite(&HasCol, sizeof(bool), 1, _pFile);

	return true;
}

void CPlatform::Load(FILE* _pFile)
{
	// 1. 오브젝트 타입을 보고 이 함수가 호출된 상황
	// 2. Room 정보 불러옴
	int Room = 0;
	fread(&Room, sizeof(int), 1, _pFile);
	SetRoom(Room);

	// 3. 포지션 불러와서 세팅
	Vec2 VecBuff = Vec2();
	fread(&VecBuff, sizeof(Vec2), 1, _pFile);
	SetPos(VecBuff);

	// 4. RowCol 불러와서 세팅
	UINT RowCnt = 0;
	fread(&RowCnt, sizeof(UINT), 1, _pFile);
	UINT ColCnt = 0;
	fread(&ColCnt, sizeof(UINT), 1, _pFile);
	m_TileMap->SetRowCol(RowCnt, ColCnt);

	// 5. UnitScale 불러와서 세팅
	UINT UWidth = 0;
	fread(&UWidth, sizeof(UINT), 1, _pFile);
	UINT UHeight = 0;
	fread(&UHeight, sizeof(UINT), 1, _pFile);
	m_TileMap->SetUnitScale(UWidth, UHeight);

	// 6. 타일맵의 타일 정보 불러와서 각 타일 세팅
	for (UINT row = 0; row < RowCnt; ++row)
	{
		for (UINT col = 0; col < ColCnt; ++col)
		{
			int len = 0;
			fread(&len, sizeof(int), 1, _pFile);

			vector<wchar_t> szBuff(len + 1);
			fread(szBuff.data(), sizeof(wchar_t), len, _pFile);

			// 타일 이름을 읽음
			wstring TileName = szBuff.data();

			// 타일 이름으로 애셋매니저에서 타일을 불러와서 현재 (row,col)에 세팅
			CTile* pTile = CAssetMgr::Get()->FindAsset<CTile>(TileName);
			if (pTile)
				m_TileMap->SetTile(row, col, pTile);
		}
	}

	// 7. Collider 여부를 읽어서 콜라이더 세팅
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
