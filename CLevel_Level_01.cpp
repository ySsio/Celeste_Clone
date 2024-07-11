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

	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos(GetSpawnPoint());
	pPlayer->SetScale(100.f, 100.f);

	AddObject(pPlayer, LAYER_TYPE::PLAYER);

	CGameMgr::Get()->SetPlayer(pPlayer);


	// Platform

	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetPos(Vec2(0.f, 0.f));
	CTileMap* pTileMap = pPlatform->GetComponent<CTileMap>();
	pTileMap->SetRowCol(25, 30);
	pTileMap->SetUnitScale(40, 40);


	wstring PaletteName = L"snow";

	for (int i = 0; i < 30; ++i)
	{
		pTileMap->SetTile(20, i, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_" + PaletteName + L"_0_0"));
		pTileMap->SetTile(21, i, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_" + PaletteName + L"_0_0"));
		pTileMap->SetTile(22, i, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_" + PaletteName + L"_0_0"));
	}
	pTileMap->SetTile(9, 0, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_" + PaletteName + L"_0_0"));
	pTileMap->SetTile(10, 0, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_" + PaletteName + L"_0_0"));
	pTileMap->SetTile(11, 0, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_" + PaletteName + L"_0_0"));

	for (int i = 5; i < 19; ++i)
	{
		pTileMap->SetTile(i, 23, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_" + PaletteName + L"_0_0"));
	}

	pTileMap->SetTile(20, 29, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Spike_Right"));
	pTileMap->SetTile(21, 29, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Spike_Right"));
	pTileMap->SetTile(22, 29, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_Spike_Right"));


	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 15; ++j)
		{
			pTileMap->SetTile(i+1, j, CAssetMgr::Get()->FindAsset<CTile>(L"Tile_" + PaletteName + L"_" + std::to_wstring(j) + L"_" + std::to_wstring(i)));
		}
	}

	pTileMap->AddCollider();

	AddObject(pPlatform, LAYER_TYPE::PLATFORM);


	// Strawberry
	CStrawBerry* pStrawberry = new CStrawBerry;
	pStrawberry->SetPos(Vec2(200.f, 400.f));
	pStrawberry->SetScale(Vec2(80.f, 80.f));

	AddObject(pStrawberry, LAYER_TYPE::OBJ);


	// Spring
	CSpring* pSpring = new CSpring;
	pSpring->SetPos(Vec2(200.f, 760.f));
	pSpring->SetScale(Vec2(80.f, 80.f));
	pSpring->SetDir(Vec2(0.f, -1.f));

	AddObject(pSpring, LAYER_TYPE::OBJ);


	// ZipMover
	CZipMover* pZip = new CZipMover;
	pZip->SetPos(Vec2(200.f, 500.f));
	pZip->SetStartPos(Vec2(200.f, 500.f));
	pZip->SetEndPos(Vec2(740.f, 500.f));
	pZip->SetTile(2,4);

	AddObject(pZip, LAYER_TYPE::OBJ);

	// �浹 ����

	CCollisionMgr::Get()->RegisterCollisionLayer(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM, true);
	CCollisionMgr::Get()->RegisterCollisionLayer(LAYER_TYPE::PLAYER, LAYER_TYPE::OBJ, true);
}