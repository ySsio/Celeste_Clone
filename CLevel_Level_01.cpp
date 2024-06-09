#include "pch.h"
#include "CLevel_Level_01.h"
#include "CEngine.h"
#include "CAssetMgr.h"
#include "CCollisionMgr.h"
#include "CTexture.h"

#include "CPlayer.h"
#include "CPlatform.h"

#include "CTileMap.h"

CLevel_Level_01::CLevel_Level_01()
{
	SetSpawnPoint(Vec2(100.f, 500.f));
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
	pTileMap->SetRowCol(3, 5);
	pTileMap->SetScale(30, 30);
	pTileMap->SetTile(0, 0, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0"));
	pTileMap->SetTile(1, 0, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0"));
	pTileMap->SetTile(2, 0, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0"));
	pTileMap->SetTile(0, 1, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0"));
	pTileMap->SetTile(1, 1, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0"));
	pTileMap->SetTile(2, 1, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0"));
	pTileMap->SetTile(0, 2, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0"));
	pTileMap->SetTile(1, 2, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0"));
	pTileMap->SetTile(2, 2, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0"));
	pTileMap->SetTile(0, 3, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0"));
	pTileMap->SetTile(1, 3, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0"));
	pTileMap->SetTile(2, 3, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0"));
	pTileMap->SetTile(0, 4, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Spike_Right"));
	pTileMap->SetTile(1, 4, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Spike_Right"));
	pTileMap->SetTile(2, 4, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Spike_Right"));


	pTileMap->AddCollider();

	AddObject(pPlatform, LAYER_TYPE::PLATFORM);

	CCollisionMgr::Get()->RegisterCollisionLayer(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM, true);
}