#pragma once
#include "CObj.h"

class CBackGround :
    public CObj
{
private:
    CSpriteRenderer*    m_Sprite;

public:
    void SetTexture(CTexture* _Tex);

public:
    virtual bool Save(FILE* _pFile);
    virtual void Load(FILE* _pFile);

public:
    virtual void Tick() override {}
    virtual void Render() override;

public:
    CBackGround();
    ~CBackGround();
};

