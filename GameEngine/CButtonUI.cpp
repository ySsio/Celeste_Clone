#include "pch.h"
#include "CButtonUI.h"

#include "CEngine.h"
#include "CTexture.h"

CButtonUI::CButtonUI()
	: m_Font(nullptr)
{
}


CButtonUI::~CButtonUI()
{
	// ��Ʈ ����
	DeleteObject(m_Font);
}


void CButtonUI::SetFont(const wstring& _Name, int _Size)
{
	DeleteObject(m_Font);

	m_Font = CreateFont(
		_Size,                     // ����
		0,                         // ��
		0,                         // ���� ����
		0,                         // ���̽����� ����
		FW_BOLD,                   // ����
		FALSE,                     // ���Ÿ�ü
		FALSE,                     // ����
		FALSE,                     // ��Ҽ�
		DEFAULT_CHARSET,           // ���ڼ�
		OUT_DEFAULT_PRECIS,        // ��� ���е�
		CLIP_DEFAULT_PRECIS,       // Ŭ���� ���е�
		DEFAULT_QUALITY,           // ��� ǰ��
		DEFAULT_PITCH | FF_SWISS,  // �۲� ���� �� ��ġ
		_Name.c_str()              // �۲� �̸�
	);
}

void CButtonUI::Tick_DerivedUI()
{
}

void CButtonUI::Render_DerivedUI()
{
	Vec2 vFinalPos = GetFinalPos();
	Vec2 vScale = GetScale();

	CSpriteRenderer* pSprite = GetSprite();

	if (pSprite->GetTex())
	{
		pSprite->Render();
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

	
	// ��Ʈ ����
	HFONT hOldFont = (HFONT)SelectObject(BackDC, m_Font);

	TextOut(BackDC
		, (int)(vFinalPos.x)
		, (int)(vFinalPos.y)
		, GetName().c_str()
		, (int)GetName().length());


	// ���� ��Ʈ�� ����
	SelectObject(BackDC, hOldFont);
	
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
