#include "pch.h"
#include "CLevel_01.h"
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

CLevel_01_01::CLevel_01_01()
{
}

CLevel_01_01::~CLevel_01_01()
{
}

void CLevel_01_01::Enter()
{
	// �� �ε�
	Load(L"\\map\\Level_01.level");

	// ���� �� ����
	MoveRoom(0);

	// Sound ���
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


	// �浹 ����
	CCollisionMgr::Get()->RegisterCollisionLayer(LAYER_TYPE::PLAYER, LAYER_TYPE::PLATFORM, true);
	CCollisionMgr::Get()->RegisterCollisionLayer(LAYER_TYPE::PLAYER, LAYER_TYPE::OBJ, true);
}