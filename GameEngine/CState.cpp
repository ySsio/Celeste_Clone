#include "pch.h"
#include "CState.h"


CState::CState()
	: m_StateMachine(nullptr)
	, m_Owner(nullptr)
	, m_BangAnim(nullptr)
	, m_BodyAnim(nullptr)
	//, m_Rigid(nullptr)
{
}

CState::~CState()
{
}