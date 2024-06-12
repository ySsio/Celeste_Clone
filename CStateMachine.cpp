#include "pch.h"
#include "CStateMachine.h"

#include "CState.h"
#include "CPlayer.h"

CStateMachine::CStateMachine()
    : m_CurState(nullptr)
{
}

CStateMachine::~CStateMachine()
{
    Release_Map(m_mapState);
}

void CStateMachine::AddState(const wstring& _StrName, CState* _State)
{
    CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwner());
    _State->SetStateMachine(this);
    _State->SetOwner(pPlayer);
    _State->SetAnimator(pPlayer->GetAnimator());
    m_mapState.emplace(_StrName, _State);
}

void CStateMachine::ChangeState(const wstring& _StrName)
{
    m_CurState = FindState(_StrName);
    m_CurState->Enter();
    assert(m_CurState);
}

CState* CStateMachine::FindState(const wstring& _StrName)
{
    auto iter = m_mapState.find(_StrName);
    if (iter != m_mapState.end())
        return iter->second;

    return nullptr;
}


void CStateMachine::FinalTick()
{
    // AnyState���� ���º�ȯ�Ǵ� ������ ���⼭ üũ, �ش�Ǵ� �� ������ ����



    // ���� state ����
    if (m_CurState)
        m_CurState->FinalTick();
}

