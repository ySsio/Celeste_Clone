#pragma once
#include "CLevel_Editor.h"

class CAnimation;

class CLevel_MapEditor :
    public CLevel_Editor
{
private:
    HMENU   m_Menu;
    Vec2    m_MouseRealPos;

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
    void SaveMap();
    void LoadMap();


public:
    CLevel_MapEditor();
    ~CLevel_MapEditor();
};

