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
    CAnimator*      m_BangAnim;
    CAnimator*      m_BodyAnim;
    //CRigidBody*     m_Rigid;
    

public:
    void SetStateMachine(CStateMachine* _StateMachine) { m_StateMachine = _StateMachine; }
    void SetOwner(CPlayer* _Owner) { m_Owner = _Owner; }
    void SetBangAnimator(CAnimator* _Anim) { m_BangAnim = _Anim; }
    void SetBodyAnimator(CAnimator* _Anim) { m_BodyAnim = _Anim; }
    //void SetRigidBody(CRigidBody* _Rigid) { m_Rigid = _Rigid; }

    CStateMachine* GetStateMachine() { return m_StateMachine; }
    CPlayer* GetOwner() { return m_Owner; }
    CAnimator* GetBangAnimator() { return m_BangAnim; }
    CAnimator* GetBodyAnimator() { return m_BodyAnim; }
    //CRigidBody* GetRigidBody() { return m_Rigid; }

    virtual void Reset() {}

public:
    virtual void PlayAnimation() = 0;

public:
    virtual void Enter() = 0;
    virtual void Exit() = 0;
    virtual void FinalTick() = 0;

public:
    CState();
    ~CState();
};

