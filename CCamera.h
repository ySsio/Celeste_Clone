#pragma once
#include "CManager.h"

class CTexture;

class CCamera :
    public CManager
{
    SINGLE(CCamera)

private:
    Vec2        m_CamPos;

    float       m_AccTime;
    float       m_Duration;

    CTexture*   m_Tex;

    CAM_EFFECT  m_CurEffect;

public:
    void SetCamEffect(CAM_EFFECT _Effect);

public:
    virtual void Init() override;
    void Tick();
    void Render();

public:
    Vec2 GetRenderPos(Vec2 _RealPos);
    Vec2 GetRealPos(Vec2 _RenderPos);

};

