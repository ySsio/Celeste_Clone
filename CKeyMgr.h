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

    UP,
    LEFT,
    DOWN,
    RIGHT,

    SPACE,
    ESC,
    ENTER,

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

public:
    KEY_STATE GetKeyState(KEY _Type) { return m_ArrKeyInfo[(UINT)_Type].state; }

public:
    virtual void Init() override;
    void Tick();

};

