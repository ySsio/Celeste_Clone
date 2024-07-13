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

    bool m_Fix;

    bool m_FlipX;

public:
    void SetOffset(Vec2 _Offset) { m_Offset = _Offset; }
    void SetTex(CTexture* _pTex);
    CTexture* GetTex() { return m_Tex; }
    void FlipX(bool _B) { m_FlipX = _B; }

	void SetFix(bool _b) { m_Fix = _b; }
    bool GetFix() { return m_Fix; }

    void ClearTex();

public:
    void Render();

public:
    CSpriteRenderer();
    ~CSpriteRenderer();
};

