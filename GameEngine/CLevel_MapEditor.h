#pragma once
#include "CLevel_Editor.h"

class CAnimation;
class CTile;
class CPlatform;
class CBackGround;

class CLevel_MapEditor :
    public CLevel_Editor
{
private:
    // GUI 관련
    Vec2    m_MouseRealPos;

    // 레벨 이름
    wstring m_LevelName;

    // 편집 중 속성
    bool    m_GeneratingRoom;
    bool    m_EditBGTile;
    bool    m_EditGameTile;
    bool    m_EditBGObj;
    bool    m_EditGameObj;
    bool    m_EditSpawnPoint;

    CTile*  m_CurTile;

    // 편집 중인 Room 정보
    Vec2    m_LT;
    Vec2    m_RB;
    Vec2    m_Pos;
    Vec2    m_Scale;
    Vec2    m_ColRow;

    CPlatform*  m_BGTile;
    CPlatform*  m_GameTile;

    CBackGround*    m_BGObj;
    CObj*           m_GameObj;


public:
    void SetCurTile(CTile* _Tile) { m_CurTile = _Tile; }
    void SetBGObj(CBackGround* _Obj) { m_BGObj = _Obj; }
    void SetGameObj(CObj* _Obj) { m_GameObj = _Obj; }

    CBackGround* GetBGObj() { return m_BGObj; }
    CObj* GetGameObj() { return m_GameObj; }

    void GenerateRoom() { m_GeneratingRoom = true; }
    void EditBGTile(bool _b) { m_EditBGTile = _b; }
    void EditGameTile(bool _b) { m_EditGameTile = _b; }

    void EditBGObj(bool _b) { m_EditBGObj = _b; }
    void EditGameObj(bool _b) { m_EditGameObj = _b; }

    void EditSpawnPoint(bool _b) { m_EditSpawnPoint = _b; }

    void SetLevelName(const wstring& _Name) { m_LevelName = _Name; }
    const wstring& GetLevelName() { return m_LevelName; }

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

