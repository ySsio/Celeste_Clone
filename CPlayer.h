#pragma once
#include "CObj.h"

class CSpriteRenderer;
class CAnimator;

class CPlayer :
    public CObj
{
private:
    CSpriteRenderer*    m_HeadSprite;
    CSpriteRenderer*    m_BodySprite;
    CAnimator*          m_HeadAnim;
    CAnimator*          m_BodyAnim;

public:
    virtual void Tick() override;
    virtual void Render() override;

public:
    CPlayer();
    CPlayer(const CPlayer& _other) = delete;
    ~CPlayer();
};

