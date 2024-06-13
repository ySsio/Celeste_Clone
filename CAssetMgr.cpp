#include "pch.h"
#include "CAssetMgr.h"

CAssetMgr::CAssetMgr()
{

}

CAssetMgr::~CAssetMgr()
{
	Release_Map(m_mapTex);
	Release_Map(m_mapAnim);
	Release_Map(m_mapSound);
	Release_Map(m_mapTile);
}

void CAssetMgr::Init()
{
	CTexture* pTex = nullptr;
	CTexture* pFlipTex = nullptr;
	// Animation »ý¼º
	tAnimFrm Frm{};
	Frm.Offset = Vec2(0.f, 0.f);
	Frm.Duration = 0.1f;
	tAnimFrm FrmFlipX(Frm);

	CAnimation* pAnim = new CAnimation;
	CAnimation* pAnimFlipX = new CAnimation;

	// Player Bang
	pTex = LoadAsset<CTexture>(L"Player_Bang_00", L"\\texture\\Player\\bangs00.png")->Stretch(Vec2(40.f, 40.f));
	Frm.Offset = Vec2(0.f, 20.f);
	Frm.Texture = pTex;
	for (int i = 0; i < 4; ++i) { pAnim->AddFrm(Frm); }

	Frm.Offset = Vec2(0.f, 28.f);
	for (int i = 0; i < 5; ++i) { pAnim->AddFrm(Frm); }

	pFlipTex = CreateFlippedTexture(L"Player_Bang_FlipX_00", pTex);
	FrmFlipX.Offset = Vec2(0.f, 20.f);
	FrmFlipX.Texture = pFlipTex;
	for (int i = 0; i < 4; ++i) { pAnimFlipX->AddFrm(FrmFlipX); }
	
	FrmFlipX.Offset = Vec2(0.f, 28.f);
	for (int i = 0; i < 5; ++i) { pAnimFlipX->AddFrm(FrmFlipX); }

	AddAnimation(L"Player_Bang", pAnim);
	AddAnimation(L"Player_Bang_FlipX", pAnimFlipX);

	// Player Idle
	pAnim = new CAnimation;
	pAnimFlipX = new CAnimation;
	Frm.Offset = Vec2(0.f, 0.f);
	FrmFlipX.Offset = Vec2(0.f, 0.f);
	for (int i = 0; i <= 8; ++i)
	{
		wstring num = i <= 9 ? L"0" + std::to_wstring(i) : std::to_wstring(i);

		pTex = LoadAsset<CTexture>(L"Player_Idle_" + num, L"\\texture\\Player\\idle" + num + L".png")->Stretch(Vec2(160.f, 160.f));
		Frm.Texture = pTex;
		pAnim->AddFrm(Frm);

		pFlipTex = CreateFlippedTexture(L"Player_Idle_FlipX_" + num, pTex);
		FrmFlipX.Texture = pFlipTex;
		pAnimFlipX->AddFrm(FrmFlipX);
	}
	AddAnimation(L"Player_Idle", pAnim);
	AddAnimation(L"Player_Idle_FlipX", pAnimFlipX);

	// Player IdleA
	pAnim = new CAnimation;
	pAnimFlipX = new CAnimation;
	for (int i = 0; i <= 11; ++i)
	{
		wstring num = i <= 9 ? L"0" + std::to_wstring(i) : std::to_wstring(i);

		pTex = LoadAsset<CTexture>(L"Player_IdleA_" + num, L"\\texture\\Player\\idleA" + num + L".png")->Stretch(Vec2(160.f, 160.f));
		Frm.Texture = pTex;
		pAnim->AddFrm(Frm);

		pFlipTex = CreateFlippedTexture(L"Player_IdleA_FlipX_" + num, pTex);
		FrmFlipX.Texture = pFlipTex;
		pAnimFlipX->AddFrm(FrmFlipX);
	}
	AddAnimation(L"Player_IdleA", pAnim);
	AddAnimation(L"Player_IdleA_FlipX", pAnimFlipX);

	// Player IdleB
	pAnim = new CAnimation;
	pAnimFlipX = new CAnimation;
	for (int i = 0; i <= 23; ++i)
	{
		wstring num = i <= 9 ? L"0" + std::to_wstring(i) : std::to_wstring(i);

		pTex = LoadAsset<CTexture>(L"Player_IdleB_" + num, L"\\texture\\Player\\idleB" + num + L".png")->Stretch(Vec2(160.f, 160.f));
		Frm.Texture = pTex;
		pAnim->AddFrm(Frm);

		pFlipTex = CreateFlippedTexture(L"Player_IdleB_FlipX_" + num, pTex);
		FrmFlipX.Texture = pFlipTex;
		pAnimFlipX->AddFrm(FrmFlipX);
	}
	AddAnimation(L"Player_IdleB", pAnim);
	AddAnimation(L"Player_IdleB_FlipX", pAnimFlipX);

	// Player IdleC
	pAnim = new CAnimation;
	pAnimFlipX = new CAnimation;
	for (int i = 0; i <= 11; ++i)
	{
		wstring num = i <= 9 ? L"0" + std::to_wstring(i) : std::to_wstring(i);

		pTex = LoadAsset<CTexture>(L"Player_IdleC_" + num, L"\\texture\\Player\\idleC" + num + L".png")->Stretch(Vec2(160.f, 160.f));
		Frm.Texture = pTex;
		pAnim->AddFrm(Frm);

		pFlipTex = CreateFlippedTexture(L"Player_IdleC_FlipX_" + num, pTex);
		FrmFlipX.Texture = pFlipTex;
		pAnimFlipX->AddFrm(FrmFlipX);
	}
	AddAnimation(L"Player_IdleC", pAnim);
	AddAnimation(L"Player_IdleC_FlipX", pAnimFlipX);

	
	// Tile
	CTile* pTile = new CTile;
	pTile->SetTexture(LoadAsset<CTexture>(L"Tile_Girder", L"\\tilesets\\girder.png"));
	pTile->SetScale(Vec2(8.f, 8.f));
	pTile->SetLT(Vec2(0.f, 0.f));
	pTile->SetDanger(false);
	pTile->SetColInfo();
	AddTile(L"Tile_Girder_0", pTile);

	pTile = new CTile;
	pTile->SetTexture(LoadAsset<CTexture>(L"Tile_Spike_Right", L"\\tilesets\\danger\\spikes\\default_right00.png"));
	pTile->SetScale(Vec2(8.f, 8.f));
	pTile->SetLT(Vec2(0.f, 0.f));
	pTile->SetDanger(true);
	pTile->SetColInfo();
	AddTile(L"Tile_Spike_Right", pTile);

}

void CAssetMgr::CreateAnimation(const wstring& _strName)
{

}

CTexture* CAssetMgr::CreateFlippedTexture(const wstring& _strName, CTexture* _pTex)
{
	CTexture* pTex = FindAsset<CTexture>(_strName);
	if (pTex)
		return pTex;

	pTex = new CTexture;
	
	int Width = _pTex->GetWidth();
	int Height = _pTex->GetHeight();

	pTex->CreateTexture(Width, Height);

	StretchBlt(pTex->GetDC()
		, 0, 0
		, Width, Height
		, _pTex->GetDC()
		, Width - 1, 0
		, -Width, Height
		, SRCCOPY);

	AddTexture(_strName, pTex);

	return pTex;
}
