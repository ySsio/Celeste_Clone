#include "pch.h"
#include "CSelectObject.h"
#include "CEngine.h"

CSelectObject::CSelectObject(HDC _dc, PEN_TYPE _Pen)
	: m_DC(_dc)
	, m_prevGDI(nullptr)
{
	m_prevGDI = (HPEN)SelectObject(_dc, CEngine::Get()->GetPen(_Pen));
}

CSelectObject::CSelectObject(HDC _dc, BRUSH_TYPE _Brush)
	: m_DC(_dc)
	, m_prevGDI(nullptr)
{
	m_prevGDI = (HBRUSH)SelectObject(_dc, CEngine::Get()->GetBrush(_Brush));
}

CSelectObject::~CSelectObject()
{
	SelectObject(m_DC, m_prevGDI);
}
