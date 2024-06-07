#pragma once
#include "CBase.h"
class CObj :
    public CBase
{
private:
    Vec2    m_Pos;
    Vec2    m_Scale;

public:
    void SetPos(float _x, float _y) { m_Pos.x = _x; m_Pos.y = _y; }
    void SetPos(Vec2 _vPos) { m_Pos = _vPos; }
    void SetScale(float _x, float _y) { m_Scale.x = _x; m_Scale.y = _y; }

    Vec2 GetPos() { return m_Pos; }
    Vec2 GetScale() { return m_Scale; }
    Vec2 GetRenderPos();

public:
    virtual void Tick() = 0;
    virtual void Render();

public:
    CObj();
    CObj(const CObj& _other);
    ~CObj();
};

