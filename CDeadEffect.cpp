#include "pch.h"
#include "CDeadEffect.h"
#include "CTimeMgr.h"

#include "CTexture.h"
#include "CAssetMgr.h"

#include "CEngine.h"



CDeadEffect::CDeadEffect()
	: m_Distance(0.f)
	, m_MaxDistance(100.f)
	, m_Count(8)
	, m_BaseColor(BANG_COLOR::WHITE)
	, m_Color(BANG_COLOR::WHITE)
	, m_SpreadDuration(0.2f)
	, m_ColorDuration(0.1f)
	, m_AccTime(0.f)
	, m_ColorAccTime(m_ColorDuration)
	, m_Tex(nullptr)
	, m_Position(vector<Vec2>(m_Count))
	, m_Rotation(0.f)
	, m_RotationDir(1.f)
	, m_Spread(true)
{
	m_Offset = Vec2(-2.5f, 42.5f);
}

CDeadEffect::~CDeadEffect()
{
}

void CDeadEffect::Tick()
{
	m_AccTime += fDT;
	m_ColorAccTime += fDT;

	// ColorDuration마다 색을 바꿈
	if (m_ColorAccTime >= m_ColorDuration)
	{
		wstring TexName = L"hair_";

		switch (m_BaseColor)
		{
		case BANG_COLOR::PINK:
			TexName += L"pink";
			break;
		case BANG_COLOR::RED:
			TexName += L"red";
			break;
		case BANG_COLOR::BLUE:
			TexName += L"blue";
			break;
		case BANG_COLOR::WHITE:
			TexName += L"white";
			break;
		default:
			break;
		}

		if (m_Color == m_BaseColor)
		{
			m_Color = BANG_COLOR::WHITE;
			m_Tex = CAssetMgr::Get()->FindAsset<CTexture>(L"hair_white")->Stretch(Vec2(40.f, 40.f));
		}
		else
		{
			m_Color = m_BaseColor;
			m_Tex = CAssetMgr::Get()->FindAsset<CTexture>(TexName)->Stretch(Vec2(40.f, 40.f));
		}

		m_ColorAccTime -= m_ColorDuration;
	}
	

	Vec2 vPos = GetPos() + m_Offset;

	// SpreadDuration까지 거리를 점점 증가시킨다 (보간)
	if (m_AccTime <= m_SpreadDuration)
	{
		float ratio = m_AccTime / m_SpreadDuration;

		if (m_Spread)
		{
			m_Distance = 0.f * (1 - ratio) + m_MaxDistance * ratio;
			if (fabs(m_MaxDistance - m_Distance) < 5.f)
			{
				m_Distance = m_MaxDistance;
			}
		}
		else
		{
			m_Distance = 0.f * ratio + m_MaxDistance * (1 - ratio);
			if (fabs(m_MaxDistance) < 5.f)
			{
				m_Distance = 0.f;
			}
		}

	}
		
	m_Rotation += 70.f * fDT * m_RotationDir; // 1초에 70도씩 회전

	// 모든 지점에 대해 포지션을 계산
	for (int i = 0; i < m_Count; ++i)
	{
		float Rad = (360.f * i / m_Count + m_Rotation) * (PI / 180.f);

		m_Position[i] = vPos + Vec2(cosf(Rad) * m_Distance, sinf(Rad) * m_Distance);
	}
}

void CDeadEffect::Render()
{
	for (int i = 0; i < m_Count; ++i)
	{
		Vec2 vPos = RENDER_POS(m_Position[i]);

		int Width = m_Tex->GetWidth();
		int Height = m_Tex->GetHeight();

		BLENDFUNCTION blend{};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(BackDC
			, (int)(vPos.x - Width / 2.f)
			, (int)(vPos.y - Height / 2.f)
			, Width, Height
			, m_Tex->GetDC()
			, 0, 0
			, Width, Height
			, blend);
	}
}
