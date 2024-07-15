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

	// ���� �� ����
	MoveRoom(0);

	// �浹 ����
	CCollisionMgr::Get()->RegisterCollisionLayer(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM, true);
	CCollisionMgr::Get()->RegisterCollisionLayer(LAYER_TYPE::PLAYER, LAYER_TYPE::OBJ, true);
}