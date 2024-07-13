#include "pch.h"
#include "CAfterImage.h"

#include "CTimeMgr.h"

#include "CTexture.h"

#include "CEngine.h"


CAfterImage::CAfterImage(CTexture* _SrcTex, float _Duration)
	: m_Duration(_Duration)
	, m_AccTime(0.f)
	, m_Tex(nullptr)
	, m_RGBA(0x805fcde4)
{ 
	m_Tex = new CTexture;
	UINT Width = _SrcTex->GetWidth();
	UINT Height = _SrcTex->GetHeight();
	m_Tex->CreateTexture(Width, Height);

	BITMAP bitmap = _SrcTex->GetBitMapInfo();

	BITMAPINFO bmi = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = bitmap.bmWidth;
	bmi.bmiHeader.biHeight = -bitmap.bmHeight; // ���� ����
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32; // 32��Ʈ ��Ʈ�� (ARGB)

	BYTE* pBits = new BYTE[bitmap.bmWidth * bitmap.bmHeight * 4];

	// �ȼ� ������ ��������
	GetDIBits(_SrcTex->GetDC(), _SrcTex->GetBitMap(), 0, bitmap.bmHeight, pBits, &bmi, DIB_RGB_COLORS);

	// ������ �ȼ� �����͸� ��Ʈ�ʿ� ����
	SetDIBits(m_Tex->GetDC(), m_Tex->GetBitMap(), 0, bitmap.bmHeight, pBits, &bmi, DIB_RGB_COLORS);

	// �޸� ����
	delete[] pBits;

	//0x805fcde4, 0x80FF0000
	FillAlphaNonZeroAreas(m_Tex->GetBitMap(), m_RGBA);
}

CAfterImage::~CAfterImage()
{
	delete m_Tex;
}

void CAfterImage::SetRGBA(UINT _RGBA)
{
	m_RGBA = _RGBA;
	FillAlphaNonZeroAreas(m_Tex->GetBitMap(), m_RGBA);
}

void CAfterImage::Init()
{
	Delete_Object(this);
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
	blend.SourceConstantAlpha = (BYTE) (255 * (1 - min(m_AccTime / m_Duration, 1.f)));
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