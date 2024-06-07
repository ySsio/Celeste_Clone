#pragma once
#include "CAsset.h"
class CTexture :
    public CAsset
{
private:
    HDC         m_DC;
    HBITMAP     m_BitMap;
    BITMAP      m_BitMapInfo;

public:
    UINT GetWidth() { return m_BitMapInfo.bmWidth; }
    UINT GetHeight() { return m_BitMapInfo.bmHeight; }
    HDC GetDC() { return m_DC; }

    CTexture* Stretch(Vec2 _Resolution);
    CTexture* Scale(float _Coef) { return Stretch(Vec2(m_BitMapInfo.bmWidth * _Coef, m_BitMapInfo.bmHeight * _Coef)); }

public:

public:
    virtual void Load(const wstring& _strRelativeFilePath) override;
   

public:
    CTexture();
    ~CTexture();
};

