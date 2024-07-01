#include "pch.h"
#include "CSelectObject.h"
#include "CEngine.h"

HFONT CSelectObject::m_Font = nullptr;

CSelectObject::CSelectObject(HDC _dc, PEN_TYPE _Pen)
	: m_DC(_dc)
	, m_prevGDI(nullptr)
{
	m_prevGDI = SelectObject(_dc, CEngine::Get()->GetPen(_Pen));
}


CSelectObject::CSelectObject(HDC _dc, BRUSH_TYPE _Brush)
	: m_DC(_dc)
	, m_prevGDI(nullptr)
{
	m_prevGDI = SelectObject(_dc, CEngine::Get()->GetBrush(_Brush));
}

void CSelectObject::SelectFont(const wstring& _Font, UINT _Size)
{
    if (m_Font)
        DeleteObject(m_Font);

    m_Font = CreateFont(
        _Size, // Font height
        0,  // Width
        0,  // Escapement
        0,  // Orientation
        FW_NORMAL,  // Weight
        FALSE,      // Italic
        FALSE,      // Underline
        FALSE,      // Strikeout
        DEFAULT_CHARSET, // Charset
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH,
        _Font.c_str()    // Font name
    );
}

CSelectObject::~CSelectObject()
{
	SelectObject(m_DC, m_prevGDI);
}
