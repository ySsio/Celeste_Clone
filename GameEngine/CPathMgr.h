#pragma once
#include "CManager.h"

class CPathMgr :
    public CManager
{
    SINGLE(CPathMgr)

private:
    wstring     m_ContentPath;
    wstring     m_SavePath;

public:
    wstring ChangeDirUp(const wstring& _Path);

public:
    const wstring& GetContentPath() { return m_ContentPath; }
    const wstring& GetSavePath() { return m_SavePath; }
    wstring GetRelativePath(const wstring& _strFilePath);
    wstring GetFileName(const wstring& _strFilePath);
    wstring GetNaiveFileName(const wstring& _strFilePath);
    wstring GetPathExtension(const wstring& _strFilePath);
    wstring GetFileDirectory(const wstring& _strFilePath);
    vector<wstring> GetFileList(const wstring& _strDirectory);

public:
    virtual void Init() override;
};

