#include "pch.h"
#include "CTextUI.h"
#include "CEngine.h"


CTextUI::CTextUI()
    : m_Font(nullptr)
{
}

CTextUI::~CTextUI()
{
    DeleteObject(m_Font);
}

void CTextUI::SetText(const wstring& _Text)
{
    m_Text = _Text;
    SIZE textSize{};
    GetTextExtentPoint32(BackDC, m_Text.c_str(), (int)m_Text.length(), &textSize);
    SetScale((float)textSize.cx, (float)textSize.cy);
}

void CTextUI::SetFont(const wstring& _Font, UINT _Size)
{
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

void CTextUI::Tick_DerivedUI()
{
}

void CTextUI::Render_DerivedUI()
{
	Vec2 vFinalPos = GetFinalPos();
	Vec2 vScale = GetScale();

    SelectObject(BackDC, m_Font);
    SELECT_PEN(BackDC, PEN_TYPE::BLUE);
    SELECT_BRUSH(BackDC, BRUSH_TYPE::HOLLOW);


    Rectangle(BackDC
        , (int)(vFinalPos.x)
        , (int)(vFinalPos.y)
        , (int)(vFinalPos.x + vScale.x)
        , (int)(vFinalPos.y + vScale.y));

	TextOut(BackDC
		, (int)vFinalPos.x
		, (int)vFinalPos.y
		, m_Text.c_str(), (int)m_Text.length());
}