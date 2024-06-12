#pragma once
#include "CBase.h"

#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CRigidBody.h"
#include "CAnimator.h"

class CStateMachine;

class CState :
    public CBase
{
private:
    CStateMachine*  m_StateMachine;
    CPlayer*        m_Owner;
    CAnimator*      m_Anim;
    //CRigidBody*     m_Rigid;
    

public:
    void SetStateMachine(CStateMachine* _StateMachine) { m_StateMachine = _StateMachine; }
    void SetOwner(CPlayer* _Owner) { m_Owner = _Owner; }
    void SetAnimator(CAnimator* _Anim) { m_Anim = _Anim; }
    //void SetRigidBody(CRigidBody* _Rigid) { m_Rigid = _Rigid; }

    CStateMachine* GetStateMachine() { return m_StateMachine; }
    CPlayer* GetOwner() { return m_Owner; }
    CAnimator* GetAnimator() { return m_Anim; }
    //CRigidBody* GetRigidBody() { return m_Rigid; }

    

public:
    virtual void Enter() = 0;
    virtual void FinalTick() = 0;

public:
    CState();
    ~CState();
};

