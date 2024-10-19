#pragma once
#include "CManager.h"


class CDebugMgr :
    public CManager
{
    SINGLE(CDebugMgr)

private:
    list<tDebugShapeInfo> m_DebugShapeList;

    bool m_DbgOnOff;

public:
    void AddDebugShape(const tDebugShapeInfo& _DebugShape) { m_DebugShapeList.push_back(_DebugShape); }

public:
    virtual void Init() override;
    void Tick();
    void Render();

};

