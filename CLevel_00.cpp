#include "pch.h"
#include "CLevel_00.h"

#include "CCollisionMgr.h"

#include "CPlayer.h"
#include "CGameMgr.h"
#include "CEngine.h"

#include "CGamePauseUI.h"

#include "CWingBerry.h"


CLevel_00::CLevel_00()
{
}

CLevel_00::~CLevel_00()
{
}

void CLevel_00::Enter()
{
	Load(L"\\map\\Level_00_Test.level");

	// 현재 룸 설정
	MoveRoom(0);

	// Player
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos(GetRooms()[GetCurRoom()].SpawnPoints[0]);
	pPlayer->SetScale(Vec2(100.f, 100.f));
	pPlayer->SetRoom(0);

	AddObject(pPlayer, LAYER_TYPE::PLAYER);

	CGameMgr::Get()->SetPlayer(pPlayer);

	// test
	

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