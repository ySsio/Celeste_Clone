#pragma once
#include "CManager.h"

class CTexture;

class CCamera :
    public CManager
{
    SINGLE(CCamera)

private:
    Vec2        m_CamPos;
    Vec2        m_CamTargetPos;

    Vec2        m_LimitLT;
    Vec2        m_LimitRB;

    float       m_AccTime;
    float       m_Duration;
    float       m_Speed;

    CTexture*   m_Tex;

    CAM_EFFECT  m_CurEffect;

public:
    void SetCamEffect(CAM_EFFECT _Effect, UINT_PTR _wParam = 0);
    void SetCamLimit(Vec2 _LT, Vec2 _RB) { m_LimitLT = _LT; m_LimitRB = _RB; }

public:
    Vec2 GetAvailableCamPos(Vec2 _Pos);

public:
    virtual void Init() override;
    void Tick();
    void Render();

public:
    Vec2 GetRenderPos(Vec2 _RealPos);
    Vec2 GetRealPos(Vec2 _RenderPos);

};

