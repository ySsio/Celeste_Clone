#pragma once
#include "CAsset.h"
#include "assert.h"

class CTexture;
class CCollider;

// Ratio !! 가로 / 세로 비율로 포지션과 스케일을 결정
// default 값은 (0.5,0.5), (1.0,1.0)
struct tColInfo
{
    Vec2    Offset;
    Vec2    Scale;
};

class CTile :
    public CAsset
{
private:
    CTexture*   m_Tex;
    Vec2        m_LT;
    Vec2        m_Scale;

    bool        m_HasCol;
    bool        m_IsDanger;

    tColInfo    m_ColInfo;

public:
    CTexture* GetTexture() { return m_Tex; }
    Vec2 GetLT() { return m_LT; }
    Vec2 GetScale() { return m_Scale; }
    bool HasCollider() { return m_HasCol; }
    bool IsDanger() { return m_IsDanger; }
    const tColInfo& GetColInfo() { return m_ColInfo; }

    void SetTexture(CTexture* _Tex) { m_Tex = _Tex; }
    void SetLT(Vec2 _LT) { m_LT = _LT; }
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

    void SetDanger(bool _b) { m_IsDanger = _b; }

    void SetColInfo() {
        m_HasCol = true;
        m_ColInfo = { Vec2(0.5, 0.5), Vec2(1.0, 1.0) };
    }

    void SetColInfo(Vec2 _RenderOffset, Vec2 _RenderScale) {
        m_HasCol = true;
        m_ColInfo = { _RenderOffset, _RenderScale };
    }

public:
    void Save(const wstring& _strRelativeFilePath);
    virtual void Load(const wstring& _strRelativeFilePath) override;

public:
    CTile();
    ~CTile();
};

