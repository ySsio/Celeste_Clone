#pragma once
#include "CObj.h"

class CBackGround :
    public CObj
{
private:
    CSpriteRenderer*    m_Sprite;

public:
    void SetTexture(CTexture* _Tex);

public:
    virtual void Tick() override {}
    virtual void Render() override;

public:
    CBackGround();
    ~CBackGround();
};

