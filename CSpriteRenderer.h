#pragma once
#include "CComponent.h"

class CTexture;

class CSpriteRenderer :
    public CComponent
{
private:
    Vec2        m_Offset;
    CTexture*   m_Tex;
    CTexture*   m_FlippedTex;

    bool m_FlipX;

public:
    void SetOffset(Vec2 _Offset) { m_Offset = _Offset; }
    void SetTexture(CTexture* _pTex);
    void FlipX(bool _B) { m_FlipX = _B; }

    void ClearTex();

public:
    void Render();

public:
    CSpriteRenderer();
    ~CSpriteRenderer();
};

