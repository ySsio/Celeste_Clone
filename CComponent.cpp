#include "pch.h"
#include "CComponent.h"

CComponent::CComponent()
	: m_Owner(nullptr)
{
}

CComponent::CComponent(const CComponent& _Other)
	: CBase(_Other)
	, m_Owner(nullptr)
{
}

CComponent::~CComponent()
{
}
