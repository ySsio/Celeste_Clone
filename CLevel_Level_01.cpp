#include "pch.h"
#include "CLevel_Level_01.h"
#include "CEngine.h"
#include "CAssetMgr.h"
#include "CCollisionMgr.h"
#include "CTexture.h"

#include "CPlayer.h"
#include "CPlatform.h"
#include "CStrawBerry.h"
#include "CSpring.h"
#include "CZipMover.h"

#include "CTileMap.h"

#include "CBackGround.h"

#include "CGameMgr.h"

#include "CCamera.h"

CLevel_Level_01::CLevel_Level_01()
{
}

CLevel_Level_01::~CLevel_Level_01()
{
}

void CLevel_Level_01::Enter()
{
	// 맵 로드
	Load(L"\\map\\.level");

	// 현재 룸 설정
	SetCurRoom(0);

	// Sound 재생
	CSound* pSound = CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\bgm\\mus_lvl1_main_synths_loop.wav");
	pSound->SetPosition(4.f);
	pSound->PlayToBGM(true);

	// Player
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos(GetRooms()[GetCurRoom()].SpawnPoints[0]);
	pPlayer->SetScale(100.f, 100.f);
	pPlayer->SetRoom(0);

	AddObject(pPlayer, LAYER_TYPE::PLAYER);

	CGameMgr::Get()->SetPlayer(pPlayer);


	//// Platform

	//CPlatform* pPlatform = new CPlatform;
	//pPlatform->SetPos(Vec2(0.f, 0.f));
	//CTileMap* pTileMap = pPlatform->GetComponent<CTileMap>();
	//pTileMap->SetRowCol(25, 30);
	//pTileMap->SetUnitScale(40, 40);


	//wstring PaletteName = L"snow";

	//for (int i = 0; i < 30; ++i)
	//{
	//	pTileMap->SetTile(20, i, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_" + PaletteName + L"_0_0"));
	//	pTileMap->SetTile(21, i, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_" + PaletteName + L"_0_0"));
	//	pTileMap->SetTile(22, i, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_" + PaletteName + L"_0_0"));
	//}
	//pTileMap->SetTile(9, 0, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_" + PaletteName + L"_0_0"));
	//pTileMap->SetTile(10, 0, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_" + PaletteName + L"_0_0"));
	//pTileMap->SetTile(11, 0, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_" + PaletteName + L"_0_0"));

	//for (int i = 5; i < 19; ++i)
	//{
	//	pTileMap->SetTile(i, 23, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_" + PaletteName + L"_0_0"));
	//}

	//pTileMap->SetTile(20, 29, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Spike_Right"));
	//pTileMap->SetTile(21, 29, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Spike_Right"));
	//pTileMap->SetTile(22, 29, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Spike_Right"));


	//for (int i = 0; i < 6; ++i)
	//{
	//	for (int j = 0; j < 15; ++j)
	//	{
	//		pTileMap->SetTile(i+1, j, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_" + PaletteName + L"_" + std::to_wstring(j) + L"_" + std::to_wstring(i)));
	//	}
	//}

	//pTileMap->AddCollider();

	//AddObject(pPlatform, LAYER_TYPE::PLATFORM);


	//// Strawberry
	//CStrawBerry* pStrawberry = new CStrawBerry;
	//pStrawberry->SetPos(Vec2(200.f, 400.f));
	//pStrawberry->SetScale(Vec2(80.f, 80.f));

	//AddObject(pStrawberry, LAYER_TYPE::OBJ);


	//// Spring
	//CSpring* pSpring = new CSpring;
	//pSpring->SetPos(Vec2(200.f, 760.f));
	//pSpring->SetScale(Vec2(80.f, 80.f));
	//pSpring->SetDir(Vec2(0.f, -1.f));

	//AddObject(pSpring, LAYER_TYPE::OBJ);


	//// ZipMover
	//CZipMover* pZip = new CZipMover;
	//pZip->SetPos(Vec2(200.f, 500.f));
	//pZip->SetStartPos(Vec2(200.f, 500.f));
	//pZip->SetEndPos(Vec2(740.f, 500.f));
	//pZip->SetTile(2,4);

	//AddObject(pZip, LAYER_TYPE::OBJ);

	// 충돌 설정

	CCollisionMgr::Get()->RegisterCollisionLayer(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM, true);
	CCollisionMgr::Get()->RegisterCollisionLayer(LAYER_TYPE::PLAYER, LAYER_TYPE::OBJ, true);
}