#pragma once
#include "CComponent.h"

class CState;

class CStateMachine :
    public CComponent
{
private:
    unordered_map<wstring, CState*> m_mapState;
    CState* m_CurState;

public:
    void AddState(const wstring& _StrName, CState* _State);
    void ChangeState(const wstring& _StrName);
    CState* FindState(const wstring& _StrName);
    

public:
    virtual void FinalTick() override;

public:
    CStateMachine();
    ~CStateMachine();
};

