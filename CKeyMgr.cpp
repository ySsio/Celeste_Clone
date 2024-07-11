#include "pch.h"
#include "CKeyMgr.h"

#include "CEngine.h"

array<int, (UINT)KEY::END> KEY_MAP
{
    'W',
    'A',
    'S',
    'D',

    'C',
    'X',
    'Z',

    VK_UP,
    VK_LEFT,
    VK_DOWN,
    VK_RIGHT,

    VK_SPACE,
    VK_ESCAPE,
    VK_BACK,
    VK_DELETE,
    VK_RETURN,

    VK_LBUTTON,
    VK_RBUTTON
};

CKeyMgr::CKeyMgr()
	: m_ArrKeyInfo{tKeyInfo{KEY_STATE::NONE,false}}
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::Init()
{
}

void CKeyMgr::Tick()
{
    //if (CEngine::Get()->GetMainHwnd() != GetFocus())
    //    return;

    // ��� Ű ���¸� ������Ʈ
    for (int i = 0; i < (UINT)KEY::END; ++i)
    {
        // Ű�� ��������
        if (GetAsyncKeyState(KEY_MAP[i]) & 0x8001)
        {
            // �� �����ӿ� Ű�� ������ �ʾ�����
            if (!m_ArrKeyInfo[i].bPrevPressed)
            {
                m_ArrKeyInfo[i].state = KEY_STATE::TAP;
            }
            // �� �����ӿ� Ű�� �����־�����
            else
            {
                m_ArrKeyInfo[i].state = KEY_STATE::PRESSED;
            }
            m_ArrKeyInfo[i].bPrevPressed = true;
        }
        else
        {
            // �� �����ӿ� Ű�� ������ �ʾ�����
            if (!m_ArrKeyInfo[i].bPrevPressed)
            {
                m_ArrKeyInfo[i].state = KEY_STATE::NONE;
            }
            // �� �����ӿ� Ű�� �����־�����
            else
            {
                m_ArrKeyInfo[i].state = KEY_STATE::RELEASED;
            }
            m_ArrKeyInfo[i].bPrevPressed = false;
        }
    }

    POINT pt{};
    GetCursorPos(&pt);
    ScreenToClient(CEngine::Get()->GetMainHwnd(), &pt);

    m_MousePos = pt;
}
