#pragma once
#include "CAsset.h"

class CTexture;

class CTile :
    public CAsset
{
private:
    CTexture*   m_Tex;
    Vec2        m_LT;
    Vec2        m_Scale;

public:
    CTexture* GetTexture() { return m_Tex; }
    Vec2 GetLT() { return m_LT; }
    Vec2 GetScale() { return m_Scale; }

    void SetTexture(CTexture* _Tex) { m_Tex = _Tex; }
    void SetLT(Vec2 _LT) { m_LT = _LT; }
    void SetScale(Vec2 _Scale) { m_Scale = _Scale; }

public:
    void Save(const wstring& _strRelativeFilePath);
    virtual void Load(const wstring& _strRelativeFilePath) override;

public:
    CTile();
    ~CTile();
};

