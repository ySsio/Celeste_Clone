#pragma once
#include "CBase.h"

class CObj;
class CTexture;

class CLevel :
    public CBase
{
private:
    array<vector<CObj*>, (UINT)LAYER_TYPE::END>     m_ArrLayerObj;
    CTexture*   m_BackGround;

    Vec2        m_CheckPoint;

public:
    virtual void Enter() = 0;
    virtual void Exit() final;

public:
    void Tick();
    void FinalTick();
    void Render();

public:
    virtual void Tick_Derived() {}

public:
    Vec2 GetSpawnPoint() { return m_CheckPoint; }
    void SetSpawnPoint(Vec2 _Spawn) { m_CheckPoint = _Spawn; }
    const vector<CObj*>& GetLayer(LAYER_TYPE _Type) { return m_ArrLayerObj[(UINT)_Type]; }

public:
    void AddObject(CObj* _Obj, LAYER_TYPE _Type);
    void SetBackGround(CTexture* _BackGround) { m_BackGround = _BackGround; }

public:
    CLevel();
    ~CLevel();
};

