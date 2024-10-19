#pragma once
#include "CComponent.h"

class CTile;
class CCollider;

// �»�� ��ġ�� Position / Offset���� ����
class CTileMap :
    public CComponent
{
private:
    UINT        m_UnitWidth;
    UINT        m_UnitHeight;
    UINT        m_RowCnt;
    UINT        m_ColCnt;

    Vec2        m_Offset;

    bool        m_HasCol;

    vector<CTile*>      m_vecTile;
    unordered_map<CCollider*, Vec2> m_mapCol;

    // Crumble
    bool        m_Crumble;
    float       m_AccTime;
    float       m_Duration;
    vector<Vec2>        m_CrumbleOffsets;

public:
    UINT GetRowCnt() { return m_RowCnt; }
    UINT GetColCnt() { return m_ColCnt; }

    UINT GetUnitWidth() { return m_UnitWidth; }
    UINT GetUnitHeight() { return m_UnitHeight; }

    void SetUnitScale(UINT _Width, UINT _Height) { m_UnitWidth = _Width; m_UnitHeight = _Height; }

    void SetRowCol(UINT _Row, UINT _Col) {
        m_RowCnt = _Row; 
        m_ColCnt = _Col;
        m_vecTile.resize(_Row * _Col);
    }
    void SetTile(UINT _Row, UINT _Col, CTile* _Tile);

    void SetOffset(Vec2 _Offset) { m_Offset = _Offset; }

    Vec2 FindCollider(CCollider* _Col);
    bool IsTileDanger(CCollider* _Col);

    const vector<CTile*>& GetTileset() { return m_vecTile; }
    bool HasCollider() { return m_HasCol; }
    void SetCollider(bool _b) { m_HasCol = _b; }
    
    void Crumble(bool _b) { m_Crumble = _b; if (_b) m_CrumbleOffsets.resize(m_RowCnt * m_ColCnt); }

public:
    void AddCollider();

public:
    virtual void FinalTick() override;
    void Render();
    

public:
    CLONE(CTileMap)
    CTileMap();
    ~CTileMap();
};

