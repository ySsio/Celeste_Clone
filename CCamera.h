#pragma once
#include "CManager.h"

class CTexture;

class CCamera :
    public CManager
{
    SINGLE(CCamera)

private:
    Vec2        m_CamPos;

public:
    virtual void Init() override;
    void Tick();

public:
    Vec2 GetRenderPos(Vec2 _RealPos);

};

