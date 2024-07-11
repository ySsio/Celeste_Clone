#pragma once
#include "CLevel_Editor.h"

class CAnimation;
class CTile;
class CPlatform;

class CLevel_MapEditor :
    public CLevel_Editor
{
private:
    // GUI 관련
    Vec2    m_MouseRealPos;

    // 편집 중 속성
    bool    m_GeneratingRoom;
    bool    m_EditBG;
    bool    m_EditGame;

    CTile*  m_CurTile;

    // 편집 중인 Room 정보
    Vec2    m_LT;
    Vec2    m_RB;
    Vec2    m_Pos;
    Vec2    m_Scale;
    Vec2    m_ColRow;

    CPlatform*  m_BGTile;
    CPlatform*  m_GameTile;


public:
    void SetCurTile(CTile* _Tile) { m_CurTile = _Tile; }
    void GenerateRoom() { m_GeneratingRoom = true; }
    void EditBG(bool _b) { m_EditBG = _b; }
    void EditGame(bool _b) { m_EditGame = _b; }

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

