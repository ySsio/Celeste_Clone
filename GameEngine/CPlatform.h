#pragma once
#include "CObj.h"

class CTileMap;

class CPlatform :
    public CObj
{
private:
    CTileMap*   m_TileMap;


public:
    void SetRowCol(UINT _Row, UINT _Col);

public:
    virtual bool Save(FILE* _pFile) override;
    virtual void Load(FILE* _pFile) override;

public:
    virtual void Tick() override;
    virtual void Render() override;

public:
    CLONE(CPlatform)
    CPlatform();
    CPlatform(const CPlatform& _Other);
    ~CPlatform();
};

