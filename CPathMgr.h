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

public:
    virtual void Init() override;
};

