#pragma once
#include "CComponent.h"

class CTexture;

class CSpriteRenderer :
    public CComponent
{
private:
    Vec2        m_Offset;
    CTexture*   m_Tex;

public:
    void SetOffset(Vec2 _Offset) { m_Offset = _Offset; }
    void SetTexture(CTexture* _pTex) { m_Tex = _pTex; }

public:
    void Render();

public:
    CSpriteRenderer();
    ~CSpriteRenderer();
};

