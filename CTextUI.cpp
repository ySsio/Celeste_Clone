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
    // ��Ʈ�� ���� �����ؾ� ��Ȯ�� ����� ����!!

    m_Text = _Text;

    // ��Ʈ ����
    HFONT hOldFont = (HFONT)SelectObject(BackDC, m_Font);

    SIZE textSize{};
    GetTextExtentPoint32(BackDC, m_Text.c_str(), (int)m_Text.length(), &textSize);
    
    SetScale(Vec2((float)textSize.cx, (float)textSize.cy));

    // ���� ��Ʈ�� ����
    SelectObject(BackDC, hOldFont);
}

void CTextUI::SetFont(const wstring& _Name, UINT _Size)
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

void CTextUI::Tick_DerivedUI()
{
}

void CTextUI::Render_DerivedUI()
{
	Vec2 vFinalPos = GetFinalPos();
	Vec2 vScale = GetScale();

    // ��Ʈ ����
    HFONT hOldFont = (HFONT)SelectObject(BackDC, m_Font);

    TextOut(BackDC
        , (int)(vFinalPos.x)
        , (int)(vFinalPos.y)
        , m_Text.c_str()
        , (int)m_Text.length());


    // ���� ��Ʈ�� ����
    SelectObject(BackDC, hOldFont);
}