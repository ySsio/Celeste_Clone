#include "pch.h"
#include "CPanelUI.h"

#include "CEngine.h"
#include "CKeyMgr.h"

CPanelUI::CPanelUI()
	: m_Movable(true)
{
}

CPanelUI::~CPanelUI()
{
}

void CPanelUI::Tick_DerivedUI()
{
	if (!m_Movable)
		return;

	Vec2 vMousePos = CKeyMgr::Get()->GetMousePos();
	Vec2 vDiff = vMousePos - m_MouseGrabPos;

	if (IsLbtnDown())
	{
		SetPos(GetPos() + vDiff);
	}

	m_MouseGrabPos = vMousePos;
}

void CPanelUI::Render_DerivedUI()
{
	Vec2 vFinalPos = GetFinalPos();
	Vec2 vScale = GetScale();

	SELECT_PEN(BackDC, PEN_TYPE::BLACK);
	SELECT_BRUSH(BackDC, BRUSH_TYPE::GRAY);

	Rectangle(BackDC
		, (int)vFinalPos.x
		, (int)vFinalPos.y
		, (int)(vFinalPos.x + vScale.x)
		, (int)(vFinalPos.y + vScale.y));
}