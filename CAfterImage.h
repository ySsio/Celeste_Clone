#pragma once
#include "CObj.h"

class CAfterImage :
    public CObj
{
private:
    float   m_Duration;
    float   m_AccTime;

    UINT    m_RGBA;

    CTexture*   m_Tex;

public:
    void SetDuration(float _Duration) { m_Duration = _Duration; }
    void SetRGBA(UINT _RGBA);

public:
    virtual void Init() override;

public:
    virtual void Tick() override;
    virtual void Render() override;


public:
    CLONE_DISABLE(CAfterImage)
    CAfterImage(CTexture* _SrcTex, float _Duration);
    ~CAfterImage();
};

