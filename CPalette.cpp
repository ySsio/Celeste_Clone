#include "pch.h"
#include "CPalette.h"

#include "CTile.h"

#include "CAssetMgr.h"
#include "CPathMgr.h"

CPalette::CPalette()
	: m_Tex(nullptr)
	, m_UnitWidth(0)
	, m_UnitHeight(0)
	, m_RowCnt(0)
	, m_ColCnt(0)
	, m_HasCol(nullptr)
	, m_IsDanger(nullptr)
{
}

CPalette::~CPalette()
{
}

void CPalette::SetPalette()
{
	SetPalette(m_Tex->GetName());
}

void CPalette::SetPalette(const wstring& _Name)
{
	for (UINT Row = 0; Row < m_RowCnt; ++Row)
	{
		for (UINT Col = 0; Col < m_ColCnt; ++Col)
		{
			CTile* pTile = new CTile;
			pTile->SetTex(m_Tex);
			pTile->SetScale(Vec2((float)m_UnitWidth, (float)m_UnitHeight));
			pTile->SetLT(Vec2((float)Col * m_UnitWidth, (float)Row * m_UnitHeight));

			if (m_HasCol)
				pTile->SetColInfo();

			pTile->SetDanger(m_IsDanger);

			CAssetMgr::Get()->AddAsset<CTile>(L"Tile_" + _Name + L"_" + std::to_wstring(Row) + L"_" + std::to_wstring(Col), pTile);

			SetTile(Row, Col, pTile);
		}
	}
}

void CPalette::SetTile(UINT _Row, UINT _Col, CTile* _Tile)
{
	assert(_Row <= m_RowCnt && _Col <= m_ColCnt);

	m_vecTile[_Row * m_ColCnt + _Col] = _Tile;
}

void CPalette::Save(const wstring& _strRelativeFilePath)
{
	wstring strFilePath = CPathMgr::Get()->GetContentPath();
	strFilePath += _strRelativeFilePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	if (!pFile) return;

	// 1. 텍스쳐의 경로 저장 (문자열 저장할 때는 문자열 길이를 먼저 저장함)
	wstring TexPath = m_Tex->GetPath();
	int len = (int)TexPath.length();
	fwrite(&len, sizeof(int), 1, pFile);
	fwrite(TexPath.c_str(), sizeof(wchar_t), len, pFile);

	// 2. 단위 너비, 높이 저장
	fwrite(&m_UnitWidth, sizeof(UINT), 1, pFile);
	fwrite(&m_UnitHeight, sizeof(UINT), 1, pFile);

	// 3. row, col 저장
	fwrite(&m_RowCnt, sizeof(UINT), 1, pFile);
	fwrite(&m_ColCnt, sizeof(UINT), 1, pFile);

	// 4. collider 여부 저장
	fwrite(&m_HasCol, sizeof(bool), 1, pFile);

	// 5. danger 여부 저장
	fwrite(&m_IsDanger, sizeof(bool), 1, pFile);

	// 6. tile 정보 저장
	for (UINT Row = 0; Row < m_RowCnt; ++Row)
	{
		for (UINT Col = 0; Col < m_ColCnt; ++Col)
		{
			CTile* pTile = m_vecTile[Row * m_ColCnt + Col];
			// 0. 타일 이름 저장
			wstring Name = pTile->GetName();
			int len = (int)Name.length();
			fwrite(&len, sizeof(int), 1, pFile);
			fwrite(Name.c_str(), sizeof(wchar_t), len, pFile);
			// 1. 텍스쳐 정보는 위의 텍스쳐를 공유할 것이므로 저장하지 않음. 로드할 때 신경쓰기
			// 2. LT 정보 저장
			Vec2 vBuff = pTile->GetLT();
			fwrite(&vBuff, sizeof(Vec2), 1, pFile);
			// 3. Scale 정보는 위의 단위 너비, 높이 정보를 공유할 것이므로 저장하지 않음. 로드할 때 신경쓰기
			// 4. Col 여부와 Danger 여부는 위의 정보를 공유할 것이므로 저장하지 않음. 로드할 때 신경쓰기
			// 5. ColInfo 저장
			tColInfo tBuff = pTile->GetColInfo();
			fwrite(&tBuff, sizeof(tColInfo), 1, pFile);
		}
	}

	fclose(pFile);
}

void CPalette::Load(const wstring& _strRelativeFilePath)
{
	// 팔레트의 정보를 분해해서 CTile 애셋으로 불러옴
	wstring strFilePath = CPathMgr::Get()->GetContentPath();
	strFilePath += _strRelativeFilePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	if (!pFile) return;

	// 1. 텍스쳐의 경로 불러오기
	int len = 0;
	fread(&len, sizeof(int), 1, pFile);

	vector<wchar_t> szBuff(len + 1);
	fread(szBuff.data(), sizeof(wchar_t), len, pFile);

	wstring TexPath = szBuff.data();
	m_Tex = CAssetMgr::Get()->LoadAsset<CTexture>(TexPath);

	// 2. 단위 너비, 높이 불러오기
	fread(&m_UnitWidth, sizeof(UINT), 1, pFile);
	fread(&m_UnitHeight, sizeof(UINT), 1, pFile);

	// 3. row, col 불러오기
	fread(&m_RowCnt, sizeof(UINT), 1, pFile);
	fread(&m_ColCnt, sizeof(UINT), 1, pFile);
	SetRowCol(m_RowCnt, m_ColCnt);

	// 4. collider 여부 불러오기
	fread(&m_HasCol, sizeof(bool), 1, pFile);

	// 5. danger 여부 불러오기
	fread(&m_IsDanger, sizeof(bool), 1, pFile);

	// 6. tile 정보 불러오기
	for (UINT Row = 0; Row < m_RowCnt; ++Row)
	{
		for (UINT Col = 0; Col < m_ColCnt; ++Col)
		{
			CTile* pTile = new CTile;
			m_vecTile[Row * m_ColCnt + Col] = pTile;

			// 0. 타일 이름 불러오기
			int len = 0;
			fread(&len, sizeof(int), 1, pFile);

			vector<wchar_t> szBuff(len + 1);
			fread(szBuff.data(), sizeof(wchar_t), len, pFile);
			wstring Name = szBuff.data();

			// 1. 텍스쳐 정보 등록
			pTile->SetTex(m_Tex);

			// 2. LT 정보 불러오기
			Vec2 vBuffer{};
			fread(&vBuffer, sizeof(Vec2), 1, pFile);
			pTile->SetLT(vBuffer);

			// 3. Scale 정보 등록
			pTile->SetScale(Vec2((float)m_UnitWidth, (float)m_UnitHeight));

			// 4.Danger 여부 등록
			pTile->SetDanger(m_IsDanger);

			// 5. ColInfo 불러오기
			tColInfo tBuffer{};
			fread(&tBuffer, sizeof(tColInfo), 1, pFile);

			if (m_HasCol)
				pTile->SetColInfo(tBuffer.Offset, tBuffer.Scale);

			// 애셋 매니저에 등록
			CAssetMgr::Get()->AddAsset<CTile>(Name, pTile);
		}
	}

	fclose(pFile);
}