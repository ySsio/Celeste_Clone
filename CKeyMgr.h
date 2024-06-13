#pragma once
#include "CManager.h"

enum class KEY
{
    W,
    A,
    S,
    D,

    C,
    X,
    Z,

    UP,
    LEFT,
    DOWN,
    RIGHT,

    SPACE,
    ESC,
    ENTER,

    LBtn,
    RBtn,

    END,
};



enum class KEY_STATE
{
    TAP,
    PRESSED,
    RELEASED,
    NONE
};

struct tKeyInfo
{
    KEY_STATE   state;
    bool        bPrevPressed;
};


class CKeyMgr :
    public CManager
{
    SINGLE(CKeyMgr)

private:
    array<tKeyInfo, (UINT)KEY::END>    m_ArrKeyInfo;
    Vec2    m_MousePos;     // 마우스를 스크린 렌더 좌표로 저장.

public:
    Vec2 GetMousePos() { return  m_MousePos; }
    KEY_STATE GetKeyState(KEY _Type) { return m_ArrKeyInfo[(UINT)_Type].state; }

public:
    virtual void Init() override;
    void Tick();

};

