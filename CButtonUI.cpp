#include "pch.h"
#include "CButtonUI.h"

#include "CEngine.h"

CButtonUI::CButtonUI()
{
}

CButtonUI::~CButtonUI()
{
}


void CButtonUI::Tick_DerivedUI()
{
}

void CButtonUI::Render_DerivedUI()
{
	Vec2 vFinalPos = GetFinalPos();
	Vec2 vScale = GetScale();

	SELECT_PEN(BackDC, PEN_TYPE::BLUE);
	SELECT_BRUSH(BackDC, BRUSH_TYPE::WHITE);

	Rectangle(BackDC
		, (int)vFinalPos.x
		, (int)vFinalPos.y
		, (int)(vFinalPos.x + vScale.x)
		, (int)(vFinalPos.y + vScale.y));

	TextOut(BackDC
		, (int)(vFinalPos.x)
		, (int)(vFinalPos.y)
		, GetName().c_str()
		, GetName().length());
}

void CButtonUI::LBtnDown()
{
}

void CButtonUI::LBtnUp()
{
}

void CButtonUI::LBtnClicked()
{
	if (m_Function)
		m_Function();
}
