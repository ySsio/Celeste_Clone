#include "pch.h"
#include "CCamera.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CAssetMgr.h"
#include "CTexture.h"

CCamera::CCamera()
	: m_AccTime(0.f)
	, m_Duration(2.f)
	, m_CurEffect(CAM_EFFECT::NONE)
	, m_Tex(nullptr)
{

}

CCamera::~CCamera()
{

}

void CCamera::SetCamEffect(CAM_EFFECT _Effect)
{
	m_CurEffect = _Effect;
	m_AccTime = 0.f;

	switch (m_CurEffect)
	{
	case CAM_EFFECT::RESPAWN:
		m_Duration = 2.f;
		m_Tex = CAssetMgr::Get()->FindAsset<CTexture>(L"Respawn_Effect");
	break;
	}
}

void CCamera::Init()
{
	Vec2 vRes = CEngine::Get()->GetResolution();
	m_CamPos = vRes / 2.f;
}

void CCamera::Tick()
{
	if (m_CurEffect != CAM_EFFECT::NONE)
		m_AccTime += fDT;

	if (m_AccTime >= m_Duration)
	{
		m_AccTime = 0.f;
		m_Tex = nullptr;
		m_CurEffect = CAM_EFFECT::NONE;
	}

	if (KEY_PRESSED(KEY::W))
	{
		m_CamPos.y -= 300.f * fDT;
	}
	if (KEY_PRESSED(KEY::S))
	{
		m_CamPos.y += 300.f * fDT;
	}
	if (KEY_PRESSED(KEY::A))
	{
		m_CamPos.x -= 300.f * fDT;
	}
	if (KEY_PRESSED(KEY::D))
	{
		m_CamPos.x += 300.f * fDT;
	}
}

void CCamera::Render()
{
	switch (m_CurEffect)
	{
	case CAM_EFFECT::RESPAWN:
	{
		Vec2 vRes = CEngine::Get()->GetResolution();

		int Width = m_Tex->GetWidth();
		int Height = m_Tex->GetHeight();

		BLENDFUNCTION blend{};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		float DestY = vRes.y - Height * m_AccTime / m_Duration;
		float SrcY = 0.f;

		if (DestY < 0.f)
		{
			SrcY = -DestY;
			DestY = 0.f;
		}


		AlphaBlend(BackDC
			, 0, (int)DestY
			, (int)vRes.x, (int)vRes.y
			, m_Tex->GetDC()
			, 0
			, (int)SrcY
			, Width, (int)(vRes.y-DestY)
			, blend);


	}
		break;
	}
}


Vec2 CCamera::GetRenderPos(Vec2 _RealPos)
{
	Vec2 vRes = CEngine::Get()->GetResolution();
	Vec2 vDiff = m_CamPos - vRes/2.f;

	return _RealPos - vDiff;
}

Vec2 CCamera::GetRealPos(Vec2 _RenderPos)
{
	Vec2 vRes = CEngine::Get()->GetResolution();
	Vec2 vDiff = m_CamPos - vRes / 2.f;

	return _RenderPos + vDiff;
}
