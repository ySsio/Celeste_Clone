#include "pch.h"
#include "CButtonUI.h"

#include "CEngine.h"
#include "CTexture.h"

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

	CTexture* pTex = GetTex();

	if (pTex)
	{
		BLENDFUNCTION blend{};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(BackDC
			, (int)(vFinalPos.x)
			, (int)(vFinalPos.y)
			, (int)vScale.x, (int)vScale.y
			, pTex->GetDC()
			, 0, 0
			, (int)vScale.x, (int)vScale.y
			, blend);
	}
	else
	{
		SELECT_PEN(BackDC, PEN_TYPE::BLUE);
		SELECT_BRUSH(BackDC, BRUSH_TYPE::WHITE);

		Rectangle(BackDC
			, (int)vFinalPos.x
			, (int)vFinalPos.y
			, (int)(vFinalPos.x + vScale.x)
			, (int)(vFinalPos.y + vScale.y));
	}

	TextOut(BackDC
		, (int)(vFinalPos.x)
		, (int)(vFinalPos.y)
		, GetName().c_str()
		, (int)GetName().length());
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
