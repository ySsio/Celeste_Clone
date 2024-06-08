#pragma once
#include "CBase.h"

class CObj;
class CTexture;

class CLevel :
    public CBase
{
private:
    array<vector<CObj*>, (UINT)LAYER_TYPE::END>     m_ArrGroupObj;
    CTexture*   m_BackGround;

public:
    virtual void Enter() = 0;
    virtual void Exit() = 0;

public:
    void Tick();
    void FinalTick();
    void Render(HDC _hDC);

public:
    const vector<CObj*>& GetGroup(LAYER_TYPE _Type) { return m_ArrGroupObj[(UINT)_Type]; }

public:
    void AddObject(CObj* _Obj, LAYER_TYPE _Type);
    void SetBackGround(CTexture* _BackGround) { m_BackGround = _BackGround; }

public:
    CLevel();
    ~CLevel();
};

