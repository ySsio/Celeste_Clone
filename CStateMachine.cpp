#include "pch.h"
#include "CStateMachine.h"

#include "CState.h"
#include "CPlayer.h"
#include "CKeyMgr.h"

#include "CLogMgr.h"

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
    _State->SetBangAnimator(pPlayer->GetBangAnimator());
    _State->SetBodyAnimator(pPlayer->GetBodyAnimator());
    m_mapState.emplace(_StrName, _State);
}

void CStateMachine::ChangeState(const wstring& _StrName)
{
    CState* pState = FindState(_StrName);
    if (pState == m_CurState)
        return;

    m_CurState = pState;
    assert(m_CurState);
    m_CurState->Enter();

    DEBUG_LOG(LOG_LEVEL::LOG, L"State Changed : " + _StrName);
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
    CPlayer* pPlayer = dynamic_cast<CPlayer*>(GetOwner());
    CRigidBody* pRigid = pPlayer->GetRigidBody();

    // AnyState에서 상태변환되는 조건을 여기서 체크, 해당되는 거 있으면 변경

    bool CanChangeState = !pRigid->IsDash() && (FindState(L"Dead") != m_CurState);

    if (CanChangeState)
    {
        if (pRigid->IsGround())
        {
            // Idle State : 아무 키도 안누르고, 바닥에 닿아있으면
            // Idle State : 속도가 0이면
            if (KEY_NONE(KEY::LEFT) && KEY_NONE(KEY::RIGHT) && KEY_NONE(KEY::C) && KEY_NONE(KEY::Z))
            //if (pRigid->GetVelocity().IsZero())
            {
                ChangeState(L"Idle");
            }

            // Run State : 바닥에 닿아있고, 좌우키 눌려있으면
            if (KEY_PRESSED(KEY::LEFT) || KEY_PRESSED(KEY::RIGHT))
            {
                ChangeState(L"Run");
            }

        }
        else
        {
            // Fall State : 바닥에 안 닿아있고 y축 속도가 양수일 때
            if (pRigid->GetVelocity().y > 0.f)
            {
                ChangeState(L"Fall");
            }
        }

        

        // Dash State : Dash 횟수가 0보다 크고, X키가 입력되었을 때
        if (pRigid->CanDash() && KEY_TAP(KEY::X))
        {
            ChangeState(L"Dash");
        }

        // Climb State : 벽에 닿음 && Z키 입력
        if (KEY_TAP(KEY::Z))
        {

        }
    }

    


    // 현재 state 진행
    if (m_CurState)
        m_CurState->FinalTick();
}

