#include "pch.h"
#include "CCamera.h"
#include "CEngine.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"

#include "CAssetMgr.h"
#include "CTexture.h"

#include "CGameMgr.h"
#include "CPlayer.h"

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

void CCamera::SetCamEffect(CAM_EFFECT _Effect, UINT_PTR _wParam)
{
	m_CurEffect = _Effect;
	m_AccTime = 0.f;

	switch (m_CurEffect)
	{
	case CAM_EFFECT::RESPAWN:
	{
		m_Duration = 2.f;
		m_Tex = CAssetMgr::Get()->FindAsset<CTexture>(L"Respawn_Effect");
	}
	break;
	case CAM_EFFECT::ROOMMOVE:
	{
		// wParam : 카메라 이동할 좌표
		m_Duration = ROOM_MOVE_DURATION;
		m_StartPos = m_CamPos;
		m_TargetPos = GetAvailableCamPos(Vec2(_wParam));
	}
	break;
	case CAM_EFFECT::SHAKE:
	{
		// wParam : 진폭
		m_Amplitude = Vec2(_wParam);
		m_Duration = 0.2f;
	}
	break;
	}
}

Vec2 CCamera::GetAvailableCamPos(Vec2 _Pos)
{
	Vec2 vRes = CEngine::Get()->GetResolution();
	Vec2 vCamPos = Vec2();

	// x좌표
	if (_Pos.x < vRes.x / 2.f + m_LimitLT.x)
	{
		vCamPos.x = vRes.x / 2.f + m_LimitLT.x;
	}
	else if (_Pos.x < m_LimitRB.x - vRes.x / 2.f)
	{
		vCamPos.x = _Pos.x;
	}
	else
	{
		vCamPos.x = m_LimitRB.x - vRes.x / 2.f;
	}

	// y좌표
	if (_Pos.y < vRes.y / 2.f + m_LimitLT.y)
	{
		vCamPos.y = vRes.y / 2.f + m_LimitLT.y;
	}
	else if (_Pos.y < m_LimitRB.y - vRes.y / 2.f)
	{
		vCamPos.y = _Pos.y;
	}
	else
	{
		vCamPos.y = m_LimitRB.y - vRes.y / 2.f;
	}
	
	return vCamPos;
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


	// 플레이어를 따라가는 카메라
	if (m_CurEffect != CAM_EFFECT::ROOMMOVE)
	{
		CPlayer* pPlayer = CGameMgr::Get()->GetPlayer();

		if (pPlayer)
		{
			Vec2 vPos = pPlayer->GetPos();
			m_CamPos = GetAvailableCamPos(vPos);
		}
	}

	switch (m_CurEffect)
	{
	case CAM_EFFECT::RESPAWN:
	break;
	case CAM_EFFECT::ROOMMOVE:
	{
		Vec2 Diff = m_TargetPos - m_CamPos;
		
		Vec2 P1 = m_StartPos + Diff / 4.f;
		Vec2 P2 = m_StartPos + Diff * 3.f / 4.f;

		float ratio = m_AccTime / m_Duration;
		ratio = easeInOut(ratio);
		m_CamPos = cubicBezier(m_StartPos, P1, P2, m_TargetPos, ratio);

		if (m_AccTime >= m_Duration)
		{
			m_CamPos = m_TargetPos;
		}
	}
	break;
	case CAM_EFFECT::SHAKE:
	{
		static float xDir = -1.f;
		static float yDir = -1.f;
		static float Frequency = 10.f;	// 1초에 10번, 즉 0.2초에 2번
		static Vec2 ShakeOffset = Vec2(0.f, 0.f);

		ShakeOffset.x += m_Amplitude.x * xDir * Frequency * 4.f * DT;
		ShakeOffset.y += m_Amplitude.y * yDir * Frequency * 4.f * DT;

		if (m_Amplitude.x < fabs(ShakeOffset.x))
		{
			ShakeOffset.x += 2 * (fabs(ShakeOffset.x) - m_Amplitude.x) * -xDir;

			xDir *= -1.f;
		}

		if (m_Amplitude.y < fabs(ShakeOffset.y))
		{
			ShakeOffset.y += 2 * (fabs(ShakeOffset.y) - m_Amplitude.y) * -yDir;

			yDir *= -1.f;
		}

		if (m_AccTime >= m_Duration)
		{
			ShakeOffset = Vec2(0.f, 0.f);
		}

		m_CamPos += ShakeOffset;

	}
	break;
	}

	if (m_AccTime >= m_Duration)
	{
		m_AccTime = 0.f;
		m_Tex = nullptr;
		m_CurEffect = CAM_EFFECT::NONE;
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
			, Width, (int)(vRes.y - DestY)
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
