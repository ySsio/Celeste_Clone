#include "pch.h"
#include "CLevel_Level_00.h"

#include "CCollisionMgr.h"

#include "CPlayer.h"
#include "CGameMgr.h"


CLevel_Level_00::CLevel_Level_00()
{
}

CLevel_Level_00::~CLevel_Level_00()
{
}

void CLevel_Level_00::Enter()
{
	Load(L"\\map\\Level_00_Test.level");

	// 현재 룸 설정
	MoveRoom(0);

	// Player
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos(GetRooms()[GetCurRoom()].SpawnPoints[0]);
	pPlayer->SetScale(100.f, 100.f);
	pPlayer->SetRoom(0);

	AddObject(pPlayer, LAYER_TYPE::PLAYER);

	CGameMgr::Get()->SetPlayer(pPlayer);

	// 충돌 설정
	CCollisionMgr::Get()->RegisterCollisionLayer(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM, true);
	CCollisionMgr::Get()->RegisterCollisionLayer(LAYER_TYPE::PLAYER, LAYER_TYPE::OBJ, true);
}