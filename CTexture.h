#pragma once
#include "CAsset.h"
class CTexture :
    public CAsset
{
private:
    HDC         m_DC;
    HBITMAP     m_BitMap;
    BITMAP      m_BitMapInfo;

    bool        m_Flipped;
    bool        m_Scaled;

public:
    UINT GetWidth() { return m_BitMapInfo.bmWidth; }
    UINT GetHeight() { return m_BitMapInfo.bmHeight; }
    HDC GetDC() { return m_DC; }
    HBITMAP GetBitMap() { return m_BitMap; }
    BITMAP GetBitMapInfo() { return m_BitMapInfo; }

    bool GetFlipped() { return m_Flipped; }

    void SetFlipped(bool _b) { m_Flipped = _b; }

public:
    CTexture* Stretch(Vec2 _Resolution);
    CTexture* Scale(float _Coef);

public:
    void Flip();
    void CreateTexture(UINT _Width, UINT _Height);

public:
    virtual void Save(const wstring& _strRelativeFilePath) override;
    virtual void Load(const wstring& _strRelativeFilePath) override;
   

public:
    CTexture();
    ~CTexture();
};

