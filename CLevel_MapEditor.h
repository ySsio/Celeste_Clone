#pragma once
#include "CLevel_Editor.h"

class CAnimation;
class CTile;

class CLevel_MapEditor :
    public CLevel_Editor
{
private:
    // GUI ����
    Vec2    m_MouseRealPos;

    Vec2    m_LT;
    Vec2    m_RB;
    Vec2    m_Pos;
    Vec2    m_Scale;
    Vec2    m_RowCol;

    // ���� �� �Ӽ�
    bool    m_GeneratingRoom;
    bool    m_EditBG;
    bool    m_EditGame;

    CTile*  m_CurTile;

    // ���� ���� ����, ��


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

