#pragma once

class CSelectObject
{
private:
	HDC			m_DC;
	HGDIOBJ		m_prevGDI; // void 포인터 타입, pen/ brush 핸들 등을 받을 수 있음

public:
	CSelectObject(HDC _dc, PEN_TYPE _Pen);
	CSelectObject(HDC _dc, BRUSH_TYPE _Brush);
	~CSelectObject();
};

