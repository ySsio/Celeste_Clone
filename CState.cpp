#include "pch.h"
#include "CState.h"


CState::CState()
	: m_StateMachine(nullptr)
	, m_Owner(nullptr)
	, m_Anim(nullptr)
	, m_Rigid(nullptr)
{
}

CState::~CState()
{
}