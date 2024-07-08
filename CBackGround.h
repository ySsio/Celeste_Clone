#pragma once
#include "CObj.h"

class CBackGround :
    public CObj
{
private:
    vector<CSpriteRenderer*>    m_Sprites;
    CTileMap*                   m_TileMap;

public:
    void AddTexture(CTexture* _Tex);

    CTileMap* GetTileMap() { return m_TileMap; }

public:
    virtual void Tick() override {}
    virtual void Render() override;

public:
    CBackGround();
    ~CBackGround();
};

