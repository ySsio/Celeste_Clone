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
    bool    m_Reset;    // 한 번 작동한 뒤 휴식

    // Sound
    bool    m_SoundA;
    bool    m_SoundB;
    bool    m_SoundC;
    bool    m_SoundD;

public:
    void SetStartPos(Vec2 _Pos) { m_StartPos = _Pos; }
    void SetEndPos(Vec2 _Pos) { m_EndPos = _Pos; }
    
    Vec2 GetStartPos() { return m_StartPos; }
    Vec2 GetEndPos() { return m_EndPos; }

    void SetDuration(float _Duration) { m_Duration = _Duration; }

    void Activate() {
        if (!m_Active && !m_Return && !m_Reset)
            m_Active = true;
    }

    void SetTile(UINT Row, UINT Col);
    UINT GetRow() { return m_TileMap->GetRowCnt(); }
    UINT GetCol() { return m_TileMap->GetColCnt(); }

public:
    virtual bool Save(FILE* _pFile) override;
    virtual void Load(FILE* _pFile) override;

public:
    virtual void Tick() override;
    virtual void Render() override;


public:
    CLONE(CZipMover)
    CZipMover();
    CZipMover(const CZipMover& _Other);
    ~CZipMover();
};

