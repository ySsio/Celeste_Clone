#pragma once
#include "CObj.h"

class CTexture;

class CDeadEffect :
    public CObj
{
private:
    Vec2    m_Offset;

    float   m_Distance;
    float   m_MaxDistance;
    int     m_Count;

    BANG_COLOR m_BaseColor;
    BANG_COLOR m_Color;

    float   m_SpreadDuration;
    float   m_ColorDuration;
    float   m_AccTime;
    float   m_ColorAccTime;

    CTexture*       m_Tex;

    vector<Vec2>    m_Position;


    float           m_Rotation;

    float           m_RotationDir;
    bool            m_Spread;


public:
    void SetBaseColor(BANG_COLOR _Color) { m_BaseColor = _Color; }
    void SetSpreadDuration(float _Duration) { m_SpreadDuration = _Duration; }
    void SetRotationDir(float _Dir) { m_RotationDir = _Dir; }

public:
    void Spread() { m_Spread = true; m_AccTime = 0.f; }
    void Gather() { m_Spread = false; m_AccTime = 0.f; }
    
public:
    virtual void Tick() override;
    virtual void Render() override;

public:
    CLONE_DISABLE(CDeadEffect)
    CDeadEffect();
    ~CDeadEffect();
};

