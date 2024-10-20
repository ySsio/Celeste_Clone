#include "pch.h"
#include "CAssetMgr.h"
#include "CEngine.h"


#include "CPalette.h"

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
	// Animation 생성
	tAnimFrm Frm{};
	Frm.Offset = Vec2(0.f, 0.f);
	Frm.Duration = 0.1f;
	tAnimFrm FrmFlipX(Frm);


	// ##########        Texture     ############

	// CamEffect - Respawn
	Vec2 vRes = CEngine::Get()->GetResolution();
	pTex = LoadAsset<CTexture>(L"\\texture\\Effects\\CamEffect\\Respawn_Effect.png")->Stretch(Vec2(vRes.x, vRes.y * 4));
	

	// BackGround
	LoadAsset<CTexture>(L"Level0_bg0", L"\\texture\\bgs\\00\\bg0.png")->Stretch(Vec2(1600.f,960.f));
	LoadAsset<CTexture>(L"Level0_bg1", L"\\texture\\bgs\\00\\bg1.png")->Stretch(Vec2(1600.f,960.f));
	LoadAsset<CTexture>(L"Level0_bg2", L"\\texture\\bgs\\00\\bg2.png")->Stretch(Vec2(1600.f,960.f));
	LoadAsset<CTexture>(L"Level0_bg3", L"\\texture\\bgs\\00\\bg3.png")->Stretch(Vec2(1600.f,960.f));

	LoadAsset<CTexture>(L"Level1_bg0", L"\\texture\\bgs\\01\\bg0.png")->Stretch(Vec2(1600.f,960.f));
	LoadAsset<CTexture>(L"Level1_bg1", L"\\texture\\bgs\\01\\bg1.png")->Stretch(Vec2(1600.f,960.f));
	LoadAsset<CTexture>(L"Level1_bg2", L"\\texture\\bgs\\01\\bg2.png")->Stretch(Vec2(1600.f,960.f));

	LoadAsset<CTexture>(L"Level3_bg0", L"\\texture\\bgs\\03\\bg0.png")->Scale(5.f);
	LoadAsset<CTexture>(L"Level3_bg1", L"\\texture\\bgs\\03\\bg1.png")->Scale(5.f);
	LoadAsset<CTexture>(L"Level3_bg2", L"\\texture\\bgs\\03\\bg2.png")->Stretch(Vec2(1600.f,1200.f));
	LoadAsset<CTexture>(L"Level3_bg2b", L"\\texture\\bgs\\03\\bg2b.png")->Scale(10.f);
	LoadAsset<CTexture>(L"Level3_bg3", L"\\texture\\bgs\\03\\bg3.png")->Scale(10.f);
	LoadAsset<CTexture>(L"Level3_bg3b", L"\\texture\\bgs\\03\\bg3b.png")->Scale(10.f);

	//LoadAsset<CTexture>(L"Level4_bg0", L"\\texture\\bgs\\04\\bg0.png")->Scale(5.f);
	//LoadAsset<CTexture>(L"Level4_bg1", L"\\texture\\bgs\\04\\bg1.png")->Scale(5.f);



	// Player Bang
	CreateFlippedTexture(LoadAsset<CTexture>(L"\\texture\\Player\\bangs_pink00.png")->Scale(5.f));
	CreateFlippedTexture(LoadAsset<CTexture>(L"\\texture\\Player\\bangs_pink01.png")->Scale(5.f));
	CreateFlippedTexture(LoadAsset<CTexture>(L"\\texture\\Player\\bangs_pink02.png")->Scale(5.f));
	CreateFlippedTexture(LoadAsset<CTexture>(L"\\texture\\Player\\bangs_red00.png")->Scale(5.f));
	CreateFlippedTexture(LoadAsset<CTexture>(L"\\texture\\Player\\bangs_red01.png")->Scale(5.f));
	CreateFlippedTexture(LoadAsset<CTexture>(L"\\texture\\Player\\bangs_red02.png")->Scale(5.f));
	CreateFlippedTexture(LoadAsset<CTexture>(L"\\texture\\Player\\bangs_blue00.png")->Scale(5.f));
	CreateFlippedTexture(LoadAsset<CTexture>(L"\\texture\\Player\\bangs_blue01.png")->Scale(5.f));
	CreateFlippedTexture(LoadAsset<CTexture>(L"\\texture\\Player\\bangs_blue02.png")->Scale(5.f));

	// Player Hair
	LoadAsset<CTexture>(L"\\texture\\Player\\hair_pink.png");
	LoadAsset<CTexture>(L"\\texture\\Player\\hair_blue.png");
	LoadAsset<CTexture>(L"\\texture\\Player\\hair_red.png");
	LoadAsset<CTexture>(L"\\texture\\Player\\hair_white.png");

	// ZipMover
	LoadAsset<CTexture>(L"\\texture\\Objects\\zipmover\\cog.png")->Scale(5.f);
	LoadAsset<CTexture>(L"\\texture\\Objects\\zipmover\\light01.png")->Scale(5.f);
	LoadAsset<CTexture>(L"\\texture\\Objects\\zipmover\\light02.png")->Scale(5.f);
	LoadAsset<CTexture>(L"\\texture\\Objects\\zipmover\\light03.png")->Scale(5.f);
	

	// ##########        Tile        ############
	CPalette* pPalette = nullptr;
	CTile* pTile = nullptr;

	vector<wstring> strList{ L"bgBrick", L"bgBrickRuined", L"bgCliffside", L"bgCore", L"bgDirt", L"bgLostLevels", L"bgReflection", L"bgSnow", L"bgSummit", L"bgTempleA", L"bgTempleB", L"bgWood", L"cement", L"cliffside", L"cliffsideAlt", L"core", L"dangerL", L"deadgrass", L"dirt", L"girder", L"grass", L"lostlevels", L"paletteL", L"poolEdges", L"reflection", L"reflectionAlt", L"rock", L"scifi", L"snow", L"starJump", L"stone", L"summit", L"summitNoSnow", L"template", L"templeA", L"templeB", L"tower", L"wood", L"woodStoneEdges" };


	// 주의 !! Palette Save Load 중 하나만 할 것!! 안 그러면 Leak 남음

	// Palette Save

	//pPalette = new CPalette;
	//pTex = LoadAsset<CTexture>(L"CrumbleOutline", L"\\texture\\Objects\\crumbleBlock\\outline.png");
	//pPalette->SetTex(pTex);
	//pPalette->SetScale(8, 8);
	//pPalette->SetRowCol(1, 4);
	//pPalette->SetDanger(false);
	//pPalette->SetCol(false);
	//pPalette->SetPalette(L"CrumbleOutline");

	//pPalette->Save(L"\\tilesets\\palette\\CrumbleOutline.palette");

	//delete pPalette;


	// Palette Load
	for (auto& name : strList)
	{
		wstring filepath = L"\\tilesets\\palette\\" + name + L".palette";

		pPalette = new CPalette;
		pPalette->Load(filepath);

		delete pPalette;
	}

	pPalette = new CPalette;
	pPalette->Load(L"\\tilesets\\palette\\zipmover_block.palette");

	delete pPalette;

	pPalette = new CPalette;
	pPalette->Load(L"\\tilesets\\palette\\CrumbleBlock.palette");

	delete pPalette;

	pPalette = new CPalette;
	pPalette->Load(L"\\tilesets\\palette\\CrumbleOutline.palette");

	delete pPalette;


	pTile = new CTile;
	pTile->SetTex(LoadAsset<CTexture>(L"Spike_Right", L"\\tilesets\\danger\\spikes\\default_right00.png"));
	pTile->SetScale(Vec2(8.f, 8.f));
	pTile->SetLT(Vec2(0.f, 0.f));
	pTile->SetDanger(true);
	pTile->SetColInfo(Vec2(0.15f, 0.5f), Vec2(0.3f,1.f));
	AddTile(L"Tile_Spike_Right_0_0", pTile);

	pTile = new CTile;
	pTile->SetTex(LoadAsset<CTexture>(L"Spike_Left", L"\\tilesets\\danger\\spikes\\default_left00.png"));
	pTile->SetScale(Vec2(8.f, 8.f));
	pTile->SetLT(Vec2(0.f, 0.f));
	pTile->SetDanger(true);
	pTile->SetColInfo(Vec2(0.85f, 0.5f), Vec2(0.3f, 1.f));
	AddTile(L"Tile_Spike_Left_0_0", pTile);

	pTile = new CTile;
	pTile->SetTex(LoadAsset<CTexture>(L"Spike_Up", L"\\tilesets\\danger\\spikes\\default_up00.png"));
	pTile->SetScale(Vec2(8.f, 8.f));
	pTile->SetLT(Vec2(0.f, 0.f));
	pTile->SetDanger(true);
	pTile->SetColInfo(Vec2(0.5f, 0.85f), Vec2(1.f, 0.3f));
	AddTile(L"Tile_Spike_Up_0_0", pTile);

	pTile = new CTile;
	pTile->SetTex(LoadAsset<CTexture>(L"Spike_Down", L"\\tilesets\\danger\\spikes\\default_down00.png"));
	pTile->SetScale(Vec2(8.f, 8.f));
	pTile->SetLT(Vec2(0.f, 0.f));
	pTile->SetDanger(true);
	pTile->SetColInfo(Vec2(0.5f, 0.15f), Vec2(1.f, 0.3f));
	AddTile(L"Tile_Spike_Down_0_0", pTile);

	pTile = new CTile;
	pTile->SetTex(LoadAsset<CTexture>(L"Invisible", L"\\texture\\Objects\\Invisible.png"));
	pTile->SetScale(Vec2(8.f, 8.f));
	pTile->SetLT(Vec2(0.f, 0.f));
	pTile->SetDanger(true);
	pTile->SetColInfo(Vec2(0.5f, 0.9f), Vec2(1.f, 0.2f));
	AddTile(L"Tile_Invisible_0_0", pTile);
}

void CAssetMgr::FlipTexture(CTexture* _pTex)
{
	_pTex->Flip();
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
	pTex->SetPath(_pTex->GetPath());
	pTex->SetFlipped(true);

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

CTexture* CAssetMgr::CreateFlippedTexture(CTexture* _pTex)
{
	wstring strName = _pTex->GetName();
	strName += L"_FlipX";

	return CreateFlippedTexture(strName, _pTex);
}

void CAssetMgr::SaveAsset(CAsset* _Asset, const wstring& _strRelativePath)
{
	_Asset->Save(_strRelativePath);
}