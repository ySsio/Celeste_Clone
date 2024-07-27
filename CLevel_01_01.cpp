#include "pch.h"
#include "CLevel_01_01.h"
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

#include "CGamePauseUI.h"

CLevel_01_01::CLevel_01_01()
{
}

CLevel_01_01::~CLevel_01_01()
{
}

void CLevel_01_01::Enter()
{
	// 맵 로드
	Load(L"\\map\\Level_01_Test.level");

	// 현재 룸 설정
	MoveRoom(0);

	// Sound 재생
	CSound* pSound = CAssetMgr::Get()->LoadAsset<CSound>(L"\\sound\\bgm\\mus_lvl1_main_synths_loop.wav");
	pSound->SetPosition(4.f);
	pSound->PlayToBGM(true);

	// Player
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetName(L"Player");
	pPlayer->SetScale(Vec2(100.f, 100.f));
	pPlayer->SetPos(GetRooms()[GetCurRoom()].SpawnPoints[0]);
	pPlayer->SetRoom(0);

	AddObject(pPlayer, LAYER_TYPE::PLAYER);

	CGameMgr::Get()->SetPlayer(pPlayer);

	// GamePauseUI
	Vec2 vRes = CEngine::Get()->GetResolution();
	CGamePauseUI* pUI = new CGamePauseUI;
	pUI->SetPos(vRes / 2.f);
	pUI->SetFix(true);
	AddObject(pUI, LAYER_TYPE::UI);

	// 충돌 설정
	CCollisionMgr::Get()->RegisterCollisionLayer(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM, true);
	CCollisionMgr::Get()->RegisterCollisionLayer(LAYER_TYPE::PLAYER, LAYER_TYPE::OBJ, true);
}