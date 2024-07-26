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
    // 폰트를 먼저 설정해야 정확한 사이즈가 나옴!!

    m_Text = _Text;

    // 폰트 선택
    HFONT hOldFont = (HFONT)SelectObject(BackDC, m_Font);

    SIZE textSize{};
    GetTextExtentPoint32(BackDC, m_Text.c_str(), (int)m_Text.length(), &textSize);
    
    SetScale(Vec2((float)textSize.cx, (float)textSize.cy));

    // 원래 폰트로 복원
    SelectObject(BackDC, hOldFont);
}

void CTextUI::SetFont(const wstring& _Name, UINT _Size)
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

void CTextUI::Tick_DerivedUI()
{
}

void CTextUI::Render_DerivedUI()
{
	Vec2 vFinalPos = GetFinalPos();
	Vec2 vScale = GetScale();

    // 폰트 선택
    HFONT hOldFont = (HFONT)SelectObject(BackDC, m_Font);

    TextOut(BackDC
        , (int)(vFinalPos.x)
        , (int)(vFinalPos.y)
        , m_Text.c_str()
        , (int)m_Text.length());


    // 원래 폰트로 복원
    SelectObject(BackDC, hOldFont);
}