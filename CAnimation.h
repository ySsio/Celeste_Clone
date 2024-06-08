#pragma once
#include "CAsset.h"

class CTexture;

struct tAnimFrm
{
    CTexture*   Texture;
    Vec2        Offset;
    float       Duration;
};

class CAnimation :
    public CAsset
{
private:
    vector<tAnimFrm>    m_vecFrm;

public:
    UINT GetFrmCount() { return (UINT)m_vecFrm.size(); }
    const tAnimFrm& GetFrm(UINT _Idx) { return m_vecFrm[_Idx]; }
    

    void AddFrm(tAnimFrm _Frame) { m_vecFrm.push_back(_Frame); }

public:
    virtual void Load(const wstring& _strRelativeFilePath) override;

public:
    CAnimation();
    ~CAnimation();
};

