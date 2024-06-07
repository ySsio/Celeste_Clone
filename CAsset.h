#pragma once
#include "CBase.h"

class CAsset :
    public CBase
{
private:
    wstring m_FilePath;

public:
    void SetPath(const wstring& _strFilePath) { m_FilePath = _strFilePath; }
    virtual void Load(const wstring& _strRelativeFilePath) = 0;
    
public:
    CAsset();
    ~CAsset();

};

