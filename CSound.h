#pragma once
#include "CAsset.h"
class CSound :
    public CAsset
{
private:

public:
    virtual void Save(const wstring& _strRelativeFilePath) override;
    virtual void Load(const wstring& _strRelativeFilePath) override;


public:
    CSound();
    ~CSound();
};