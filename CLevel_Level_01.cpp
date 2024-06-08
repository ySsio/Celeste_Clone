#include "pch.h"
#include "CLevel_Level_01.h"
#include "CEngine.h"
#include "CAssetMgr.h"
#include "CTexture.h"

#include "CPlayer.h"
#include "CPlatform.h"

#include "CTileMap.h"

CLevel_Level_01::CLevel_Level_01()
{

}

CLevel_Level_01::~CLevel_Level_01()
{
}

void CLevel_Level_01::Enter()
{
	CTexture* pBackGround = CAssetMgr::Get()->LoadAsset<CTexture>(L"bg0", L"\\texture\\bg0.png");
	Vec2 vRes = CEngine::Get()->GetResolution();
	pBackGround->Stretch(vRes);

	SetBackGround(pBackGround);

	CObj* pPlayer = new CPlayer;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos(450.f, 450.f);
	pPlayer->SetScale(100.f, 100.f);

	AddObject(pPlayer, LAYER_TYPE::PLAYER);

	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(100.f, 500.f);
	CTileMap* pTileMap = pPlatform->GetComponent<CTileMap>();
	pTileMap->SetRowCol(1, 5);
	pTileMap->SetScale(20, 20);
	pTileMap->SetTile(0, 0, CAssetMgr::Get()->LoadAsset<CTile>(L"Tile_Girder_0", L""));
	pTileMap->SetTile(0, 1, CAssetMgr::Get()->LoadAsset<CTile>(L"Tile_Girder_0", L""));
	pTileMap->SetTile(0, 2, CAssetMgr::Get()->LoadAsset<CTile>(L"Tile_Girder_0", L""));
	pTileMap->SetTile(0, 3, CAssetMgr::Get()->LoadAsset<CTile>(L"Tile_Girder_0", L""));
	pTileMap->SetTile(0, 4, CAssetMgr::Get()->LoadAsset<CTile>(L"Tile_Girder_0", L""));
	
	AddObject(pPlatform, LAYER_TYPE::PLATFORM);
}

void CLevel_Level_01::Exit()
{
}