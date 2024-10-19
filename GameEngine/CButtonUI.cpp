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
	// 폰트 삭제
	DeleteObject(m_Font);
}


void CButtonUI::SetFont(const wstring& _Name, int _Size)
{
	DeleteObject(m_Font);

	m_Font = CreateFont(
		_Size,                     // 높이
		0,                         // 폭
		0,                         // 기울기 각도
		0,                         // 베이스라인 각도
		FW_BOLD,                   // 굵기
		FALSE,                     // 이탤릭체
		FALSE,                     // 밑줄
		FALSE,                     // 취소선
		DEFAULT_CHARSET,           // 문자셋
		OUT_DEFAULT_PRECIS,        // 출력 정밀도
		CLIP_DEFAULT_PRECIS,       // 클리핑 정밀도
		DEFAULT_QUALITY,           // 출력 품질
		DEFAULT_PITCH | FF_SWISS,  // 글꼴 가족 및 피치
		_Name.c_str()              // 글꼴 이름
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

	
	// 폰트 선택
	HFONT hOldFont = (HFONT)SelectObject(BackDC, m_Font);

	TextOut(BackDC
		, (int)(vFinalPos.x)
		, (int)(vFinalPos.y)
		, GetName().c_str()
		, (int)GetName().length());


	// 원래 폰트로 복원
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
