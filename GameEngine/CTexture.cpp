#include "pch.h"
#include "CTexture.h"
#include "CEngine.h"
#include "CPathMgr.h"

CTexture::CTexture()
	: m_DC(nullptr)
	, m_BitMap(nullptr)
	, m_BitMapInfo{}
	, m_Flipped(false)
	, m_Scaled(false)
{
}

CTexture::~CTexture()
{
	DeleteDC(m_DC);
	DeleteObject(m_BitMap);
}

CTexture* CTexture::Stretch(Vec2 _Resolution)
{
	if (_Resolution.x == m_BitMapInfo.bmWidth && _Resolution.y == m_BitMapInfo.bmHeight)
		return this;

	HDC hStretchDC = CreateCompatibleDC(MainDC);
	HBITMAP hStretchBitmap = CreateCompatibleBitmap(MainDC, (int)_Resolution.x, (int)_Resolution.y);
	DeleteObject(SelectObject(hStretchDC, hStretchBitmap));

	StretchBlt(hStretchDC
		, 0, 0
		, (int)_Resolution.x, (int)_Resolution.y
		, m_DC
		, 0,0
		, m_BitMapInfo.bmWidth, m_BitMapInfo.bmHeight
		, SRCCOPY);

	DeleteDC(m_DC);
	DeleteObject(m_BitMap);

	m_DC = hStretchDC;
	m_BitMap = hStretchBitmap;
	GetObject(m_BitMap, sizeof(BITMAP), &m_BitMapInfo);

	return this;
}

CTexture* CTexture::Scale(float _Coef)
{
	if (m_Scaled)
		return this;

	m_Scaled = true;
	return Stretch(Vec2(m_BitMapInfo.bmWidth * _Coef, m_BitMapInfo.bmHeight * _Coef));
}

void CTexture::Flip()
{
	HDC hStretchDC = CreateCompatibleDC(MainDC);
	HBITMAP hStretchBitmap = CreateCompatibleBitmap(MainDC, m_BitMapInfo.bmWidth, m_BitMapInfo.bmHeight);
	DeleteObject(SelectObject(hStretchDC, hStretchBitmap));

	m_Flipped = !m_Flipped;

	StretchBlt(hStretchDC
		, 0, 0
		, m_BitMapInfo.bmWidth, m_BitMapInfo.bmHeight
		, m_DC
		, m_BitMapInfo.bmWidth - 1, 0
		, -m_BitMapInfo.bmWidth, m_BitMapInfo.bmHeight
		, SRCCOPY);

	DeleteDC(m_DC);
	DeleteObject(m_BitMap);

	m_DC = hStretchDC;
	m_BitMap = hStretchBitmap;
	GetObject(m_BitMap, sizeof(BITMAP), &m_BitMapInfo);
}

void CTexture::CreateTexture(UINT _Width, UINT _Height)
{
	m_DC = CreateCompatibleDC(MainDC);
	m_BitMap = CreateCompatibleBitmap(MainDC, _Width, _Height);
	DeleteObject(SelectObject(m_DC, m_BitMap));

	GetObject(m_BitMap, sizeof(BITMAP), &m_BitMapInfo);
}

void CTexture::Save(const wstring& _strRelativeFilePath)
{
}

void CTexture::Load(const wstring& _strRelativeFilePath)
{
	wstring strFilePath = CPathMgr::Get()->GetContentPath();
	strFilePath += _strRelativeFilePath;

	wchar_t szExt[50] {};
	_wsplitpath_s(strFilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 50);
	
	if (wcscmp(szExt, L".bmp") == 0 || wcscmp(szExt, L".BMP") == 0)
	{
		m_BitMap = (HBITMAP)LoadImage(nullptr, strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	}
	else if (wcscmp(szExt, L".png") == 0 || wcscmp(szExt, L".PNG") == 0)
	{
		GdiplusStartupInput input{};
		ULONG_PTR gdiplustoken = 0;
		GdiplusStartup(&gdiplustoken, &input, nullptr);

		Bitmap* pBitmap = new Bitmap(strFilePath.c_str());

		pBitmap->GetHBITMAP(Color(0, 0, 0, 0), &m_BitMap);

		delete pBitmap;

		GdiplusShutdown(gdiplustoken);
	}


	m_DC = CreateCompatibleDC(MainDC);
	DeleteObject(SelectObject(m_DC, m_BitMap));

	GetObject(m_BitMap, sizeof(BITMAP), &m_BitMapInfo);

}
