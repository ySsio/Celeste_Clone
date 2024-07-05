#include "pch.h"
#include "CSpriteRenderer.h"

#include "CObj.h"
#include "CEngine.h"
#include "CTexture.h"

#include "CAssetMgr.h"

CSpriteRenderer::CSpriteRenderer()
	: m_Tex(nullptr)
	, m_FlippedTex(nullptr)
	, m_FlipX(false)
{
}

CSpriteRenderer::~CSpriteRenderer()
{
}

void CSpriteRenderer::SetTexture(CTexture* _pTex)
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
	bmi.bmiHeader.biHeight = -bitmap.bmHeight; // ���� ����
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32; // 32��Ʈ ��Ʈ�� (ARGB)

	BYTE* pBits = new BYTE[bitmap.bmWidth * bitmap.bmHeight * 4];

	// �ȼ� ������ ��������
	GetDIBits(m_Tex->GetDC(), m_Tex->GetBitMap(), 0, bitmap.bmHeight, pBits, &bmi, DIB_RGB_COLORS);

	// ��Ʈ�� �ȼ��� RGBA 0 ������ ä���
	memset(pBits, 0, bitmap.bmWidth * bitmap.bmHeight * 4);

	// ������ �ȼ� �����͸� ��Ʈ�ʿ� ����
	SetDIBits(m_Tex->GetDC(), m_Tex->GetBitMap(), 0, bitmap.bmHeight, pBits, &bmi, DIB_RGB_COLORS);

	// �޸� ����
	delete[] pBits;
}

void CSpriteRenderer::Render()
{
	if (!m_Tex || (m_FlipX && !m_FlippedTex))
		return;

	CObj* pOwner = GetOwner();

	Vec2 FinalOffset = m_MaxDistance;
	CTexture* RenderTex = m_Tex;
	if (m_FlipX)
	{
		FinalOffset.x *= -1;
		RenderTex = m_FlippedTex;
	}

	Vec2 vPos = pOwner->GetRenderPos() + FinalOffset;
	int Width = RenderTex->GetWidth();
	int Height = RenderTex->GetHeight();


	BLENDFUNCTION blend{};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(BackDC
		, (int)(vPos.x - Width / 2.f)
		, (int)(vPos.y - Height / 2.f)
		, Width, Height
		, RenderTex->GetDC()
		, 0, 0
		, Width, Height
		, blend);

}
