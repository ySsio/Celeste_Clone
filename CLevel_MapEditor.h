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
    Vec2 GetTileLT(Vec2 _ClickPos);     // Ŭ���� ��ġ�� ���Ե� Ÿ���� �»�� ��ǥ�� ��ȯ
    Vec2 GetTileRB(Vec2 _ClickPos);     // Ŭ���� ��ġ�� ���Ե� Ÿ���� ���ϴ� ��ǥ�� ��ȯ
    Vec2 GetTileCenter(Vec2 _ClickPos); // Ŭ���� ��ġ�� ���Ե� Ÿ���� �߾� ��ǥ�� ��ȯ

public:


public:
    void SaveMap();
    void LoadMap();


public:
    CLevel_MapEditor();
    ~CLevel_MapEditor();
};

