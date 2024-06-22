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
    bool                m_Flipped;

public:
    const vector<tAnimFrm>& GetAllFrm() { return m_vecFrm; }
    void SetAllFrm(const vector<tAnimFrm>& _AllFrm) { m_vecFrm = _AllFrm; }

    UINT GetFrmCount() { return (UINT)m_vecFrm.size(); }
    tAnimFrm& GetFrm(UINT _Idx) { return m_vecFrm[_Idx]; }
    
    float GetDuration() { return m_Duration; }

    void AddFrm(tAnimFrm _Frame) { m_vecFrm.push_back(_Frame); m_Duration += _Frame.Duration; }
    void SetFlipped(bool _b) { m_Flipped = _b; }

public:
    virtual void Save(const wstring& _strRelativeFilePath) override;
    virtual void Load(const wstring& _strRelativeFilePath) override;

public:
    CAnimation();
    ~CAnimation();
};

