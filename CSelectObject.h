#pragma once

class CSelectObject
{
private:
	HDC			m_DC;
	HGDIOBJ		m_prevGDI; // void ������ Ÿ��, pen/ brush �ڵ� ���� ���� �� ����

public:
	CSelectObject(HDC _dc, PEN_TYPE _Pen);
	CSelectObject(HDC _dc, BRUSH_TYPE _Brush);
	~CSelectObject();
};

