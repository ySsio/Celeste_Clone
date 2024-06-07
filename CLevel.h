#pragma once
#include "CBase.h"

class CObj;
class CTexture;

class CLevel :
    public CBase
{
private:
    array<vector<CObj*>, (UINT)GROUP_TYPE::END>     m_ArrGroupObj;
    CTexture*   m_BackGround;

public:
    virtual void Enter() = 0;
    virtual void Exit() = 0;

public:
    void Tick();
    void Render(HDC _hDC);

public:
    void AddObject(CObj* _Obj, GROUP_TYPE _Type) { m_ArrGroupObj[(UINT)_Type].push_back(_Obj); }
    void SetBackGround(CTexture* _BackGround) { m_BackGround = _BackGround; }

public:
    CLevel();
    ~CLevel();
};

