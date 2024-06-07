#include "pch.h"
#include "CCamera.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

CCamera::CCamera()
{

}

CCamera::~CCamera()
{

}

void CCamera::Init()
{
	Vec2 vRes = CEngine::Get()->GetResolution();
	m_CamPos = vRes / 2.f;
}

void CCamera::Tick()
{
	if (KEY_PRESSED(KEY::UP))
	{
		m_CamPos.y -= 300.f * fDT;
	}
	if (KEY_PRESSED(KEY::DOWN))
	{
		m_CamPos.y += 300.f * fDT;
	}
	if (KEY_PRESSED(KEY::LEFT))
	{
		m_CamPos.x -= 300.f * fDT;
	}
	if (KEY_PRESSED(KEY::RIGHT))
	{
		m_CamPos.x += 300.f * fDT;
	}
}


Vec2 CCamera::GetRenderPos(Vec2 _RealPos)
{
	Vec2 vRes = CEngine::Get()->GetResolution();
	Vec2 vDiff = m_CamPos - vRes/2.f;

	return _RealPos - vDiff;
}
