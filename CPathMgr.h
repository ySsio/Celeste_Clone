#pragma once
#include "CManager.h"

class CPathMgr :
    public CManager
{
    SINGLE(CPathMgr)

private:
    wstring     m_ContentPath;

public:
    void ChangeDirUp(wstring& _Path);

public:
    const wstring& GetContentPath() { return m_ContentPath; }
    wstring GetFileName(const wstring& _strFilePath);
    wstring GetNaiveFileName(const wstring& _strFilePath);
    wstring GetPathExtension(const wstring& _strFilePath);

public:
    virtual void Init() override;
};

