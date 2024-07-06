#include "pch.h"
#include "CAssetMgr.h"
#include "CEngine.h"


#include "CPalette.h"

CAssetMgr::CAssetMgr()
{

}

CAssetMgr::~CAssetMgr()
{
	Release_Map(m_mapTex);
	Release_Map(m_mapAnim);
	Release_Map(m_mapSound);
	Release_Map(m_mapTile);
}

void CAssetMgr::Init()
{
	CTexture* pTex = nullptr;
	CTexture* pFlipTex = nullptr;
	// Animation »ý¼º
	tAnimFrm Frm{};
	Frm.Offset = Vec2(0.f, 0.f);
	Frm.Duration = 0.1f;
	tAnimFrm FrmFlipX(Frm);


	// ##########        Texture     ############

	// CamEffect - Respawn
	Vec2 vRes = CEngine::Get()->GetResolution();
	pTex = LoadAsset<CTexture>(L"\\texture\\Effects\\CamEffect\\Respawn_Effect.png")->Stretch(Vec2(vRes.x, vRes.y * 4));
	

	// Player Bang
	CreateFlippedTexture(LoadAsset<CTexture>(L"\\texture\\Player\\bangs_pink00.png")->Scale(5.f));
	CreateFlippedTexture(LoadAsset<CTexture>(L"\\texture\\Player\\bangs_pink01.png")->Scale(5.f));
	CreateFlippedTexture(LoadAsset<CTexture>(L"\\texture\\Player\\bangs_pink02.png")->Scale(5.f));
	CreateFlippedTexture(LoadAsset<CTexture>(L"\\texture\\Player\\bangs_red00.png")->Scale(5.f));
	CreateFlippedTexture(LoadAsset<CTexture>(L"\\texture\\Player\\bangs_red01.png")->Scale(5.f));
	CreateFlippedTexture(LoadAsset<CTexture>(L"\\texture\\Player\\bangs_red02.png")->Scale(5.f));
	CreateFlippedTexture(LoadAsset<CTexture>(L"\\texture\\Player\\bangs_blue00.png")->Scale(5.f));
	CreateFlippedTexture(LoadAsset<CTexture>(L"\\texture\\Player\\bangs_blue01.png")->Scale(5.f));
	CreateFlippedTexture(LoadAsset<CTexture>(L"\\texture\\Player\\bangs_blue02.png")->Scale(5.f));

	// Player Hair
	LoadAsset<CTexture>(L"\\texture\\Player\\hair_pink.png");
	LoadAsset<CTexture>(L"\\texture\\Player\\hair_blue.png");
	LoadAsset<CTexture>(L"\\texture\\Player\\hair_red.png");
	LoadAsset<CTexture>(L"\\texture\\Player\\hair_white.png");
	
	// ##########        Tile        ############
	CPalette* pPalette = nullptr;
	CTile* pTile = nullptr;

	pPalette = new CPalette;
	pTex = LoadAsset<CTexture>(L"\\tilesets\\girder.png");
	pPalette->SetTex(pTex);
	pPalette->SetScale(8, 8);
	pPalette->SetRowCol(15, 6);
	pPalette->SetDanger(false);
	pPalette->SetCol(true);
	pPalette->SetPalette();


	pPalette->Save(L"\\tilesets\\palette\\girder.palette");

	delete pPalette;

	pPalette = new CPalette;
	pPalette->Load(L"\\tilesets\\palette\\girder.palette");

	delete pPalette;


	pTile = new CTile;
	pTile->SetTexture(LoadAsset<CTexture>(L"Tile_Spike_Right", L"\\tilesets\\danger\\spikes\\default_right00.png"));
	pTile->SetScale(Vec2(8.f, 8.f));
	pTile->SetLT(Vec2(0.f, 0.f));
	pTile->SetDanger(true);
	pTile->SetColInfo();
	AddTile(L"Tile_Spike_Right", pTile);

}

void CAssetMgr::FlipTexture(CTexture* _pTex)
{
	_pTex->Flip();
}

void CAssetMgr::CreateAnimation(const wstring& _strName)
{
}

CTexture* CAssetMgr::CreateFlippedTexture(const wstring& _strName, CTexture* _pTex)
{
	CTexture* pTex = FindAsset<CTexture>(_strName);
	if (pTex)
		return pTex;

	pTex = new CTexture;
	
	int Width = _pTex->GetWidth();
	int Height = _pTex->GetHeight();

	pTex->CreateTexture(Width, Height);
	pTex->SetPath(_pTex->GetPath());
	pTex->SetFlipped(true);

	StretchBlt(pTex->GetDC()
		, 0, 0
		, Width, Height
		, _pTex->GetDC()
		, Width - 1, 0
		, -Width, Height
		, SRCCOPY);

	AddTexture(_strName, pTex);

	return pTex;
}

CTexture* CAssetMgr::CreateFlippedTexture(CTexture* _pTex)
{
	wstring strName = _pTex->GetName();
	strName += L"_FlipX";

	return CreateFlippedTexture(strName, _pTex);
}

void CAssetMgr::SaveAsset(CAsset* _Asset, const wstring& _strRelativePath)
{
	_Asset->Save(_strRelativePath);
}