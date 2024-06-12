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
    float               m_Duration;

public:
    UINT GetFrmCount() { return (UINT)m_vecFrm.size(); }
    const tAnimFrm& GetFrm(UINT _Idx) { return m_vecFrm[_Idx]; }
    
    float GetDuration() { return m_Duration; }

    void AddFrm(tAnimFrm _Frame) { m_vecFrm.push_back(_Frame); m_Duration += _Frame.Duration; }

public:
    void Save(const wstring& _strFilePath);
    virtual void Load(const wstring& _strRelativeFilePath) override;

public:
    CAnimation();
    ~CAnimation();
};

