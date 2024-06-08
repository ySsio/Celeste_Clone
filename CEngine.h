#pragma once
#include "global.h"

class CEngine
{
	SINGLE(CEngine)

private:
	HWND		m_MainHwnd;
	HDC			m_MainDC;
	Vec2		m_Resolution;

	array<HPEN, (UINT)PEN_TYPE::END>			m_ArrPen;
	array<HBRUSH, (UINT)BRUSH_TYPE::END>		m_ArrBrush;

	HDC			m_BackBufferDC;
	HBITMAP		m_BackBuffer;

public:
	HWND GetMainHwnd() { return m_MainHwnd; }
	HDC GetMainDC() { return m_MainDC; }
	HDC GetBackDC() { return m_BackBufferDC; }
	HBITMAP GetBackBitmap() { return m_BackBuffer; }
	HPEN GetPen(PEN_TYPE _Type) { return m_ArrPen[(UINT)_Type]; }
	HBRUSH GetBrush(BRUSH_TYPE _Type) { return m_ArrBrush[(UINT)_Type]; }

public:
	Vec2 GetResolution() { return m_Resolution; }
	void CreateGDIObject();

public:
	void Init(HWND _hwnd, int _Width, int _Height);
	void Progress();
	void Render();
};

