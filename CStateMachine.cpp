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

    // ���� ���¸� ��������
    if (m_CurState)
        m_CurState->Exit();

    // ��û�� state�� ���� state�� ����
    m_CurState = pState;
    assert(m_CurState); // ��ϵ��� ���� state�� ��û�Ǿ����� ����

    // ���ο� ���� state�� ����
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

    // AnyState���� ���º�ȯ�Ǵ� ������ ���⼭ üũ, �ش�Ǵ� �� ������ ����

    bool CanChangeState = FindState(L"Dead") != m_CurState &&  FindState(L"Dash") != m_CurState ;

    if (CanChangeState)
    {
        if (pPlayer->IsGround())
        {
            // Idle State : �ƹ� Ű�� �ȴ�����, �ٴڿ� ���������
            if (KEY_NONE(KEY::LEFT) && KEY_NONE(KEY::RIGHT) && KEY_NONE(KEY::C) && KEY_NONE(KEY::Z))
            {
                ChangeState(L"Idle");
            }
        }
        else
        {
            if (!pPlayer->IsWall())
            {
                // Fall State : �ٴ��̶� ���� �� ����ְ� y�� �ӵ��� ����� ��
                if (pRigid->GetVelocity().y > 0.f)
                {
                    ChangeState(L"Fall");
                }
            }
        }

        // Climb State : �ٴڿ� �� ����ְ� ������ ������� ��
        // ZŰ �Ǵ� �¿�Ű �������� ��
        if (pPlayer->IsWall()
            && (KEY_PRESSED(KEY::Z) || KEY_PRESSED(KEY::LEFT) || KEY_PRESSED(KEY::RIGHT)))
        {
            ChangeState(L"Climb");
        }

        // Dash State : Dash Ƚ���� 0���� ũ��, XŰ�� �ԷµǾ��� ��
        if (pPlayer->GetDashCount() > 0 && KEY_TAP(KEY::X))
        {
            ChangeState(L"Dash");
        }

    }


    // ���� state ����
    if (m_CurState)
        m_CurState->FinalTick();
}

