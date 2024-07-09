#pragma once
#include "CObj.h"


class CZipMover :
    public CObj
{
private:
    Vec2    m_StartPos;
    Vec2    m_EndPos;

    Vec2    m_Dir;

    float   m_StartDuration;
    float   m_Duration;
    float   m_StopDuration;

    float   m_AccTime;

    CRigidBody*         m_RigidBody;
    CTileMap*           m_TileMap;
    CCollider*          m_Collider;
    CSpriteRenderer*    m_SpriteRenderer;

    bool    m_Active;
    bool    m_Return;

public:
    void SetStartPos(Vec2 _Pos) { m_StartPos = _Pos; }
    void SetEndPos(Vec2 _Pos) { m_EndPos = _Pos; }

    void SetDuration(float _Duration) { m_Duration = _Duration; }

    void Activate() {
        if (!m_Active && !m_Return)
            m_Active = true;
    }

    void SetTile(UINT Row, UINT Col);

public:
    virtual void Tick() override;
    virtual void Render() override;


public:
    CZipMover();
    ~CZipMover();
};

