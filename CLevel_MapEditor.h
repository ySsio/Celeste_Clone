#pragma once
#include "CLevel_Editor.h"

class CAnimation;
class CTile;

class CLevel_MapEditor :
    public CLevel_Editor
{
private:
    Vec2    m_MouseRealPos;

    Vec2    m_LT;
    Vec2    m_RB;
    Vec2    m_Pos;
    Vec2    m_Scale;
    Vec2    m_RowCol;

    bool    m_GeneratingRoom;

    CTile*  m_CurTile;

public:
    void SetCurTile(CTile* _Tile) { m_CurTile = _Tile; }


public:
    virtual void Enter() override;

public:
    virtual void Tick_Derived() override;
    virtual void Render_Derived() override;

public:
    Vec2 GetTileLT(Vec2 _ClickPos);     // 클릭한 위치가 포함된 타일의 좌상단 좌표를 반환
    Vec2 GetTileRB(Vec2 _ClickPos);     // 클릭한 위치가 포함된 타일의 우하단 좌표를 반환
    Vec2 GetTileCenter(Vec2 _ClickPos); // 클릭한 위치가 포함된 타일의 중앙 좌표를 반환

public:


public:
    void SaveMap();
    void LoadMap();


public:
    CLevel_MapEditor();
    ~CLevel_MapEditor();
};

