#pragma once
#include "CAsset.h"

class CTexture;
class CTile;

class CPalette :
    public CAsset
{
private:
    CTexture*   m_Tex;

    UINT        m_UnitWidth;
    UINT        m_UnitHeight;
    UINT        m_RowCnt;
    UINT        m_ColCnt;

    vector<CTile*>      m_vecTile;

    bool        m_HasCol;
    bool        m_IsDanger;


public:
    UINT GetRowCnt() { return m_RowCnt; }
    UINT GetColCnt() { return m_ColCnt; }

    void SetTex(CTexture* _Tex) { m_Tex = _Tex; }

    void SetScale(UINT _Width, UINT _Height) { m_UnitWidth = _Width; m_UnitHeight = _Height; }

    void SetRowCol(UINT _Row, UINT _Col) {
        m_RowCnt = _Row;
        m_ColCnt = _Col;
        m_vecTile.resize(_Row * _Col);
    }

    void SetCol(bool _b) { m_HasCol = _b; }
    void SetDanger(bool _b) { m_IsDanger = _b; }

    void SetPalette();

private:
    void SetTile(UINT _Row, UINT _Col, CTile* _Tile);


public:
    virtual void Save(const wstring& _strRelativeFilePath) override;
    virtual void Load(const wstring& _strRelativeFilePath) override;

public:
    CPalette();
    ~CPalette();
};

