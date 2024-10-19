#pragma once
#include "CBase.h"

class CAsset :
    public CBase
{
private:
    wstring     m_FilePath; // Relative Path

public:
    const wstring& GetPath() { return m_FilePath; }

public:
    void SetPath(const wstring& _strFilePath) { m_FilePath = _strFilePath; }
    virtual void Save(const wstring& _strRelativeFilePath) = 0;
    virtual void Load(const wstring& _strRelativeFilePath) = 0;

    
public:
    CLONE_DISABLE(CAsset)
    CAsset();
    ~CAsset();

};

