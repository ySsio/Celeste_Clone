#include "pch.h"
#include "CTextBoxUI.h"
#include "CEngine.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CTextBoxUI::CTextBoxUI()
	: m_Active(false)
	, m_CursorPos(0)
	, m_CursorVisible(false)
	, m_Integer(false)
	, m_Float(false)
{
	
}

CTextBoxUI::~CTextBoxUI()
{
	

}

void CTextBoxUI::AddChar(WPARAM wParam)
{
	if (m_Integer)
	{
		if (!(('0' <= wParam && wParam <= '9') || wParam == '-'))
			return;
	}

	if (m_Float)
	{
		if (!(('0' <= wParam && wParam <= '9') || wParam == '.' || wParam == '-'))
			return;
	}

	m_Text.insert(m_CursorPos, 1, (wchar_t)wParam);
	++m_CursorPos;
}

void CTextBoxUI::Tick_DerivedUI()
{
	if (!m_Active)
	{
		m_CursorVisible = false;
		return;
	}


	if (KEY_TAP(KEY::LEFT))
	{
		if (m_CursorPos > 0)
			--m_CursorPos;
	}
	if (KEY_TAP(KEY::RIGHT))
	{
		if (m_CursorPos < m_Text.length())
		{
			++m_CursorPos;
		}
	}
	if (KEY_TAP(KEY::BACK))
	{
		if (m_CursorPos > 0)
		{
			m_Text.erase(m_CursorPos-1, 1);
			--m_CursorPos;
		}
	}
	if (KEY_TAP(KEY::DEL))
	{
		if (m_CursorPos < m_Text.length())
		{
			m_Text.erase(m_CursorPos, 1);
		}
	}

	static float const Duration = 0.5f;
	static float AccTime = 0.f;

	if (AccTime >= Duration)
	{
		AccTime -= Duration;
		m_CursorVisible = !m_CursorVisible;
	}

	AccTime += fDT;
}

void CTextBoxUI::Render_DerivedUI()
{
	Vec2 vFinalPos = GetFinalPos();
	Vec2 vScale = GetScale();

	Rectangle(BackDC
		, (int)(vFinalPos.x)
		, (int)(vFinalPos.y)
		, (int)(vFinalPos.x + vScale.x)
		, (int)(vFinalPos.y + vScale.y));

	Vec2 vTextPos = vFinalPos + Vec2(5.f, 4.f);

	TextOut(BackDC
		, (int)(vTextPos.x)
		, (int)(vTextPos.y)
		, m_Text.c_str(), (int)m_Text.length());

	if (m_CursorVisible)
	{
		SIZE textSize{};
		GetTextExtentPoint32(BackDC, m_Text.c_str(), m_CursorPos, &textSize);
		int cursorX = (int)vTextPos.x + textSize.cx;
		int cursorY = (int)vTextPos.y;
		MoveToEx(BackDC, cursorX, cursorY, NULL);
		LineTo(BackDC, cursorX, cursorY + vScale.y - 6.f);
	}

}


