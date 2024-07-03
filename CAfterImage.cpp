#include "pch.h"
#include "CAfterImage.h"

#include "CTimeMgr.h"

#include "CTexture.h"

#include "CEngine.h"


CAfterImage::CAfterImage(CTexture* _SrcTex, float _Duration)
	: m_Duration(_Duration)
	, m_AccTime(0.f)
	, m_Tex(nullptr)
{ 
	m_Tex = new CTexture;
	UINT Width = _SrcTex->GetWidth();
	UINT Height = _SrcTex->GetHeight();
	m_Tex->CreateTexture(Width, Height);

	BITMAP bitmap = _SrcTex->GetBitMapInfo();

	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = bitmap.bmWidth;
	bmi.bmiHeader.biHeight = -bitmap.bmHeight; // 상하 반전
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32; // 32비트 비트맵 (ARGB)

	BYTE* pBits = new BYTE[bitmap.bmWidth * bitmap.bmHeight * 4];

	// 픽셀 데이터 가져오기
	GetDIBits(_SrcTex->GetDC(), _SrcTex->GetBitMap(), 0, bitmap.bmHeight, pBits, &bmi, DIB_RGB_COLORS);

	// 수정된 픽셀 데이터를 비트맵에 설정
	SetDIBits(m_Tex->GetDC(), m_Tex->GetBitMap(), 0, bitmap.bmHeight, pBits, &bmi, DIB_RGB_COLORS);

	// 메모리 해제
	delete[] pBits;

	//0x805fcde4, 0x80FF0000
	FillAlphaNonZeroAreas(m_Tex->GetBitMap(), 0x805fcde4);
}

CAfterImage::~CAfterImage()
{
	delete m_Tex;
}

void CAfterImage::Tick()
{
	m_AccTime += fDT;

	if (m_AccTime > m_Duration)
		Delete_Object(this);
}

void CAfterImage::Render()
{
	UINT Width = m_Tex->GetWidth();
	UINT Height = m_Tex->GetHeight();

	Vec2 vPos = GetRenderPos();

	BLENDFUNCTION blend{};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(BackDC
		, (int)(vPos.x - Width / 2.f)
		, (int)(vPos.y - Height / 2.f)
		, Width, Height
		, m_Tex->GetDC()
		, 0, 0
		, Width, Height
		, blend);
}