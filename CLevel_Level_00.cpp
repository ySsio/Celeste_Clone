#include "pch.h"
#include "CLevel_Level_00.h"

#include "CCollisionMgr.h"


CLevel_Level_00::CLevel_Level_00()
{
}

CLevel_Level_00::~CLevel_Level_00()
{
}

void CLevel_Level_00::Enter()
{
	Load(L"\\map\\Level_0_Test.level");

	// 현재 룸 설정
	MoveRoom(0);

	// 충돌 설정
	CCollisionMgr::Get()->RegisterCollisionLayer(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM, true);
	CCollisionMgr::Get()->RegisterCollisionLayer(LAYER_TYPE::PLAYER, LAYER_TYPE::OBJ, true);
}