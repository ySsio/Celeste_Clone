#include "pch.h"
#include "CLevel_Level_01.h"
#include "CEngine.h"
#include "CAssetMgr.h"
#include "CCollisionMgr.h"
#include "CTexture.h"

#include "CPlayer.h"
#include "CPlatform.h"

#include "CTileMap.h"

#include "CBackGround.h"

CLevel_Level_01::CLevel_Level_01()
{
	SetSpawnPoint(Vec2(450.f, 300.f));
}

CLevel_Level_01::~CLevel_Level_01()
{
}

void CLevel_Level_01::Enter()
{
	Vec2 vRes = CEngine::Get()->GetResolution();

	// BackGround

	CBackGround* pBackGround = new CBackGround;
	pBackGround->SetPos(Vec2(vRes.x / 2.f, vRes.y / 2.f));
	AddObject(pBackGround, LAYER_TYPE::BACKGROUND); 

	CTexture* pBgTex = CAssetMgr::Get()->LoadAsset<CTexture>(L"Level1_bg1", L"\\texture\\bgs\\01\\bg1.png");
	pBgTex->Stretch(vRes);
	pBackGround->AddTexture(pBgTex);

	//pBackGround = new CBackGround;
	//pBackGround->SetPos(Vec2(vRes.x, 0.f));
	//AddObject(pBackGround, LAYER_TYPE::BACKGROUND);

	//pBgTex = CAssetMgr::Get()->LoadAsset<CTexture>(L"Level3_bg2", L"\\texture\\bgs\\03\\bg2.png");
	//pBgTex->Stretch(Vec2(vRes.x * 3.f/2.f ,vRes.y * 2.f));
	//pBackGround->AddTexture(pBgTex);

	pBackGround = new CBackGround;
	pBackGround->SetPos(vRes/2.f);
	AddObject(pBackGround, LAYER_TYPE::BACKGROUND);

	pBgTex = CAssetMgr::Get()->LoadAsset<CTexture>(L"Level0_bg3",L"\\texture\\bgs\\00\\bg3.png");
	pBgTex->Stretch(vRes);
	pBackGround->AddTexture(pBgTex);


	// Player

	CObj* pPlayer = new CPlayer;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos(GetSpawnPoint());
	pPlayer->SetScale(100.f, 100.f);

	AddObject(pPlayer, LAYER_TYPE::PLAYER);


	// Platform

	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(200.f, 200.f));
	CTileMap* pTileMap = pPlatform->GetComponent<CTileMap>();
	pTileMap->SetRowCol(15, 20);
	pTileMap->SetScale(40, 40);

	for (int i = 0; i < 20; ++i)
	{
		pTileMap->SetTile(12, i, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0_0"));
		pTileMap->SetTile(13, i, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0_0"));
		pTileMap->SetTile(14, i, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0_0"));
	}
	pTileMap->SetTile(12, 19, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Spike_Right"));
	pTileMap->SetTile(13, 19, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Spike_Right"));
	pTileMap->SetTile(14, 19, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Spike_Right"));


	for (int i = 5; i < 10; ++i)
	{
		pTileMap->SetTile(5, i, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0_1"));
		pTileMap->SetTile(6, i, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0_1"));
		pTileMap->SetTile(7, i, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0_1"));
	}

	for (int i = 0; i < 15; ++i)
	{
		pTileMap->SetTile(i, 0, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Girder_0_2"));
	}

	pTileMap->AddCollider();

	AddObject(pPlatform, LAYER_TYPE::PLATFORM);

	CCollisionMgr::Get()->RegisterCollisionLayer(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM, true);
}