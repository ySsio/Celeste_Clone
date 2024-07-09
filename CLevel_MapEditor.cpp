#include "pch.h"
#include "CLevel_MapEditor.h"

#include "CEngine.h"
#include "CPathMgr.h"
#include "CAssetMgr.h"

#include "CKeyMgr.h"

#include "CCamera.h"
#include "CStrawBerry.h"

CLevel_MapEditor::CLevel_MapEditor()
	: m_Menu(nullptr)
{
	m_Menu = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_GAMEENGINE));
}

CLevel_MapEditor::~CLevel_MapEditor()
{
	DestroyMenu(m_Menu);
}

void CLevel_MapEditor::Enter()
{
	// 편집 툴 (새 윈도우)를 띄움
	SetMenu(CEngine::Get()->GetMainHwnd(), m_Menu);
	CEngine::Get()->ChangeWindowResolution();

	// Strawberry
	CStrawBerry* pStrawberry = new CStrawBerry;
	pStrawberry->SetPos(Vec2(200.f, 400.f));
	pStrawberry->SetScale(Vec2(80.f, 80.f));

	AddObject(pStrawberry, LAYER_TYPE::OBJ);

}

void CLevel_MapEditor::Tick_Derived()
{
	// 마우스가 가리키는 실제좌표를 계산
	m_MouseRealPos = CCamera::Get()->GetRealPos(CKeyMgr::Get()->GetMousePos());


}

void CLevel_MapEditor::Render_Derived()
{
	// 마우스 실제좌표에서 가장 가까운 TILE_SCALE의 배수로 내림 한 X, Y좌표를
	// 다시 렌더 좌표로 변환해서 출력
	Vec2 vLT = RENDER_POS(GetTileLT(m_MouseRealPos));
	Vec2 vRB = RENDER_POS(GetTileRB(m_MouseRealPos));

	SELECT_PEN(BackDC, PEN_TYPE::ORANGE);
	SELECT_BRUSH(BackDC, BRUSH_TYPE::HOLLOW);

	Rectangle(BackDC
		, (int)vLT.x, (int)vLT.y, (int)vRB.x, (int)vRB.y);
}

Vec2 CLevel_MapEditor::GetTileLT(Vec2 _ClickPos)
{
	float X = floor(m_MouseRealPos.x / TILE_SCALE) * TILE_SCALE;
	float Y = floor(m_MouseRealPos.y / TILE_SCALE) * TILE_SCALE;

	return Vec2(X, Y);
}

Vec2 CLevel_MapEditor::GetTileRB(Vec2 _ClickPos)
{
	float X = floor(m_MouseRealPos.x / TILE_SCALE) * TILE_SCALE + TILE_SCALE;
	float Y = floor(m_MouseRealPos.y / TILE_SCALE) * TILE_SCALE + TILE_SCALE;

	return Vec2(X, Y);
}

Vec2 CLevel_MapEditor::GetTileCenter(Vec2 _ClickPos)
{
	float X = floor(m_MouseRealPos.x / TILE_SCALE) * TILE_SCALE + TILE_SCALE / 2.f;
	float Y = floor(m_MouseRealPos.y / TILE_SCALE) * TILE_SCALE + TILE_SCALE / 2.f;

	return Vec2(X,Y);
}

void CLevel_MapEditor::SaveMap()
{
}

void CLevel_MapEditor::LoadMap()
{
}


