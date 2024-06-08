#pragma once
#include "CObj.h"

class CSpriteRenderer;
class CAnimator;

class CPlayer :
    public CObj
{
private:
    CSpriteRenderer*    m_HeadSprite;
    CAnimator*          m_HeadAnim;
    CAnimator*          m_BodyAnim;

    CCollider*          m_Collider;

public:
    virtual void Tick() override;
    virtual void Render() override;

public:
    CPlayer();
    CPlayer(const CPlayer& _other) = delete;
    ~CPlayer();
};

