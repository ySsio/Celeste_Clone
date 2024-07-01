#pragma once

class CSelectObject
{
private:
	HDC			m_DC;
	HGDIOBJ		m_prevGDI; // void ������ Ÿ��, pen/ brush �ڵ� ���� ���� �� ����
	
public:
	static HFONT		m_Font;

public:
	void static SelectFont(const wstring& _Font, UINT _Size);

public:
	CSelectObject(HDC _dc, PEN_TYPE _Pen);
	CSelectObject(HDC _dc, BRUSH_TYPE _Brush);
	~CSelectObject();
};

