#include "pch.h"
#include "CLevel_Level_01.h"
#include "CPlayer.h"
#include "CTexture.h"
#include "CAssetMgr.h"
#include "CEngine.h"

CLevel_Level_01::CLevel_Level_01()
{

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
	pPlayer->SetPos(450.f, 450.f);
	pPlayer->SetScale(100.f, 100.f);

	AddObject(pPlayer, GROUP_TYPE::PLAYER);


}

void CLevel_Level_01::Exit()
{
}