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
	pPlayer->SetPos(Vec2(450.f, 300.f));
	pPlayer->SetScale(100.f, 100.f);

	AddObject(pPlayer, LAYER_TYPE::PLAYER);

	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(200.f, 200.f));
	CTileMap* pTileMap = pPlatform->GetComponent<CTileMap>();
	pTileMap->SetRowCol(15, 20);
	pTileMap->SetScale(40, 40);

	for (int i = 0; i < 20; ++i)
	{
		pTileMap->SetTile(12, i, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0"));
		pTileMap->SetTile(13, i, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0"));
		pTileMap->SetTile(14, i, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0"));
	}
	pTileMap->SetTile(12, 19, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Spike_Right"));
	pTileMap->SetTile(13, 19, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Spike_Right"));
	pTileMap->SetTile(14, 19, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Spike_Right"));

	for (int i = 0; i < 15; ++i)
	{
		pTileMap->SetTile(i, 0, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0"));
	}

	pTileMap->AddCollider();

	AddObject(pPlatform, LAYER_TYPE::PLATFORM);

	CCollisionMgr::Get()->RegisterCollisionLayer(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM, true);
}