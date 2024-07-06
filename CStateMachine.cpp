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

    // 현재 상태를 빠져나옴
    if (m_CurState)
        m_CurState->Exit();

    // 요청한 state을 현재 state로 설정
    m_CurState = pState;
    assert(m_CurState); // 등록되지 않은 state로 요청되었으면 에러

    // 새로운 현재 state로 진입
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

    bool CanChangeState = FindState(L"Dead") != m_CurState &&  FindState(L"Dash") != m_CurState ;

    if (CanChangeState)
    {
        if (pPlayer->IsGround())
        {
            // Idle State : 아무 키도 안누르고, 바닥에 닿아있으면
            if (KEY_NONE(KEY::LEFT) && KEY_NONE(KEY::RIGHT) && KEY_NONE(KEY::C) && KEY_NONE(KEY::Z))
            {
                ChangeState(L"Idle");
            }
        }
        else
        {
            if (!pPlayer->IsWall())
            {
                // Fall State : 바닥이랑 벽에 안 닿아있고 y축 속도가 양수일 때
                if (pRigid->GetVelocity().y > 0.f)
                {
                    ChangeState(L"Fall");
                }
            }
        }

        // Climb State : 바닥에 안 닿아있고 벽에만 닿아있을 떄
        // Z키 또는 좌우키 눌려있을 떄
        if (pPlayer->IsWall()
            && (KEY_PRESSED(KEY::Z) || KEY_PRESSED(KEY::LEFT) || KEY_PRESSED(KEY::RIGHT)))
        {
            ChangeState(L"Climb");
        }

        // Dash State : Dash 횟수가 0보다 크고, X키가 입력되었을 때
        if (pPlayer->GetDashCount() > 0 && KEY_TAP(KEY::X))
        {
            ChangeState(L"Dash");
        }

    }


    // 현재 state 진행
    if (m_CurState)
        m_CurState->FinalTick();
}

