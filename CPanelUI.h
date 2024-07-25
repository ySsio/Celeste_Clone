#pragma once
#include "CUI.h"

class CPanelUI :
    public CUI
{
private:
    Vec2    m_MouseGrabPos; 

    bool    m_Movable;

public:
    void SetMovable(bool _b) { m_Movable = _b; }

public:
    virtual bool Save(FILE* _pFile);
    virtual void Load(FILE* _pFile);

public:
    virtual void Tick_DerivedUI() override;
    virtual void Render_DerivedUI() override;

public:
    CLONE(CPanelUI)
    CPanelUI();
    ~CPanelUI();
};

