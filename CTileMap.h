#pragma once
#include "CComponent.h"

class CTile;
class CCollider;

// �»�� ��ġ�� Position
class CTileMap :
    public CComponent
{
private:
    UINT        m_UnitWidth;
    UINT        m_UnitHeight;
    UINT        m_RowCnt;
    UINT        m_ColCnt;

    vector<CTile*>      m_vecTile;
    vector<CCollider*>  m_vecCol;

public:
    UINT GetRowCnt() { return m_RowCnt; }
    UINT GetColCnt() { return m_ColCnt; }

    void SetScale(UINT _Width, UINT _Height) { m_UnitWidth = _Width; m_UnitHeight = _Height; }

    void SetRowCol(UINT _Row, UINT _Col) {
        m_RowCnt = _Row; 
        m_ColCnt = _Col;
        m_vecTile.resize(_Row * _Col);
    }
    void SetTile(UINT _Row, UINT _Col, CTile* _Tile);

    Vec2 FindCollider(CCollider* _Col);
    bool IsTileDanger(UINT _Row, UINT _Col);
    bool IsTileDanger(Vec2 _RowCol);
    bool IsTileDanger(CCollider* _Col);

public:
    void AddCollider();

public:
    virtual void FinalTick() override;
    void Render();
    

public:
    CTileMap();
    ~CTileMap();
};

