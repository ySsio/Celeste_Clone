#pragma once
#include "CObj.h"

class CCrumbleBlock :
    public CObj
{
private:
    CTileMap*           m_BlockTile;
    CTileMap*           m_OutlineTile;
    CCollider*          m_Collider;

    float               m_AccTime;
    float               m_Duration;
    float               m_ResetDuration;

    bool                m_Touch;
    bool                m_Active;

public:
    void SetTile(UINT Col); // 무조건 row는 1

    void Activate() { m_Touch = true; }

    void Crumble(bool _b);

    void Active();
    void Reset();

public:
    virtual bool Save(FILE* _pFile) override;
    virtual void Load(FILE* _pFile) override;

public:
    virtual void Tick() override;
    virtual void Render() override;


public:
    CLONE(CCrumbleBlock)
    CCrumbleBlock();
    CCrumbleBlock(const CCrumbleBlock& _Other);
    ~CCrumbleBlock();
};

