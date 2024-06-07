#pragma once
#include "CAsset.h"



class CAnimation :
    public CAsset
{
private:

public:
    virtual void Load(const wstring& _strRelativeFilePath) override;


public:
    CAnimation();
    ~CAnimation();
};

