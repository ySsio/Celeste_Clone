#include "pch.h"
#include "CSpriteRenderer.h"

#include "CObj.h"
#include "CEngine.h"
#include "CTexture.h"

#include "CAssetMgr.h"

CSpriteRenderer::CSpriteRenderer()
	: m_Tex(nullptr)
	, m_FlippedTex(nullptr)
	, m_Fix(false)
	, m_FlipX(false)
{
}


CSpriteRenderer::~CSpriteRenderer()
{
}

void CSpriteRenderer::SetTex(CTexture* _pTex)
{
	m_Tex = _pTex;

	wstring strKey = _pTex->GetName();
	strKey += L"_FlipX";

	m_FlippedTex = CAssetMgr::Get()->CreateFlippedTexture(strKey, _pTex);
}

void CSpriteRenderer::ClearTex()
{
	BITMAP bitmap = m_Tex->GetBitMapInfo();

	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = bitmap.bmWidth;
	bmi.bmiHeader.biHeight = -bitmap.bmHeight; // 상하 반전
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32; // 32비트 비트맵 (ARGB)

	BYTE* pBits = new BYTE[bitmap.bmWidth * bitmap.bmHeight * 4];

	// 픽셀 데이터 가져오기
	GetDIBits(m_Tex->GetDC(), m_Tex->GetBitMap(), 0, bitmap.bmHeight, pBits, &bmi, DIB_RGB_COLORS);

	// 비트맵 픽셀을 RGBA 0 값으로 채우기
	memset(pBits, 0, bitmap.bmWidth * bitmap.bmHeight * 4);

	// 수정된 픽셀 데이터를 비트맵에 설정
	SetDIBits(m_Tex->GetDC(), m_Tex->GetBitMap(), 0, bitmap.bmHeight, pBits, &bmi, DIB_RGB_COLORS);

	// 메모리 해제
	delete[] pBits;
}

void CSpriteRenderer::Render()
{
	if (!m_Tex || (m_FlipX && !m_FlippedTex))
		return;

	CObj* pOwner = GetOwner();

	Vec2 FinalOffset = m_Offset;
	CTexture* RenderTex = m_Tex;
	if (m_FlipX)
	{
		FinalOffset.x *= -1;
		RenderTex = m_FlippedTex;
	}

	Vec2 vPos = m_Fix ? pOwner->GetPos() + FinalOffset : pOwner->GetRenderPos() + FinalOffset;
	int Width = RenderTex->GetWidth();
	int Height = RenderTex->GetHeight();

	
	BLENDFUNCTION blend{};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	if (!m_PartRender)
	{
		m_PartLT = Vec2(0.f, 0.f);
		m_PartRB = Vec2(1.f, 1.f);
	}

	AlphaBlend(BackDC
		, (int)(vPos.x - Width * (m_PartRB.x - m_PartLT.x) / 2.f)
		, (int)(vPos.y - Height * (m_PartRB.y - m_PartLT.y) / 2.f)
		, (int)(Width * (m_PartRB.x - m_PartLT.x))
		, (int)(Height * (m_PartRB.y - m_PartLT.y))
		, RenderTex->GetDC()
		, (int)(Width * m_PartLT.x)
		, (int)(Height * m_PartLT.y)
		, (int)(Width * (m_PartRB.x - m_PartLT.x))
		, (int)(Height * (m_PartRB.y - m_PartLT.y))
		, blend);
}
