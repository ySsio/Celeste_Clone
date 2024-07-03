#pragma once
#include "CObj.h"

class CAfterImage :
    public CObj
{
private:
    float   m_Duration;
    float   m_AccTime;

    CTexture*   m_Tex;

public:
    void SetDuration(float _Duration) { m_Duration = _Duration; }


public:
    virtual void Tick() override;
    virtual void Render() override;


public:
    CAfterImage(CTexture* _SrcTex, float _Duration);
    ~CAfterImage();
};

