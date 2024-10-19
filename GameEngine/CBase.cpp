#include "pch.h"
#include "CBase.h"

UINT CBase::g_ID = 0;

CBase::CBase()
	: m_ID(g_ID++)
{
}

CBase::CBase(const CBase& _other)
	: m_ID(g_ID++)
	, m_Name(_other.m_Name)
{
}

CBase::~CBase()
{
	
}
