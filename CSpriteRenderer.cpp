#include "pch.h"
#include "CSpriteRenderer.h"

#include "CObj.h"
#include "CEngine.h"
#include "CTexture.h"

CSpriteRenderer::CSpriteRenderer()
	: m_Tex(nullptr)
{
}

CSpriteRenderer::~CSpriteRenderer()
{
}

void CSpriteRenderer::Render()
{
	CObj* pOwner = GetOwner();

	Vec2 vPos = pOwner->GetRenderPos() + m_Offset;

	BLENDFUNCTION blend{};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(BackDC
		, (int)(vPos.x - m_Tex->GetWidth() / 2.f)
		, (int)(vPos.y - m_Tex->GetHeight() / 2.f)
		, m_Tex->GetWidth(), m_Tex->GetHeight()
		, m_Tex->GetDC()
		, 0, 0
		, m_Tex->GetWidth(), m_Tex->GetHeight()
		, blend);
}
