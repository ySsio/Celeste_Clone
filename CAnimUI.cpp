#include "pch.h"
#include "CAnimUI.h"
#include "CEngine.h"
#include "CTexture.h"
#include "CAnimation.h"
#include "CTimeMgr.h"

CAnimUI::CAnimUI()
	: m_Bang(nullptr)
	, m_Body(nullptr)
	, m_BangFrm(0)
	, m_BodyFrm(0)
	, m_BangMaxFrm(0)
	, m_BodyMaxFrm(0)
	, m_Play(false)
{
}

CAnimUI::~CAnimUI()
{
}

void CAnimUI::SetBang(CAnimation* _Tex)
{
	assert(_Tex);
	m_Bang = _Tex;
	m_BangFrm = 0;
	m_BangMaxFrm = m_Bang->GetFrmCount();
}

void CAnimUI::SetBody(CAnimation* _Tex)
{
	assert(_Tex);
	m_Body = _Tex;
	m_BodyFrm = 0;
	m_BodyMaxFrm = m_Body->GetFrmCount();
}

void CAnimUI::Tick_DerivedUI()
{
	if (!m_Play)
		return;

	static float BangAccTime = 0.f;
	static float BodyAccTime = 0.f;
	BangAccTime += fDT;
	BodyAccTime += fDT;

	if (m_Bang)
	{
		float BangDuration = m_Bang->GetFrm(m_BangFrm).Duration;

		if (BangAccTime >= BangDuration)
		{
			++m_BangFrm;
			BangAccTime -= BangDuration;
		}

		if (m_BangFrm == m_BangMaxFrm)
			m_BangFrm = 0;
	}

	if (m_Body)
	{
		float BodyDuration = m_Body->GetFrm(m_BodyFrm).Duration;

		if (BodyAccTime >= BodyDuration)
		{
			++m_BodyFrm;
			BodyAccTime -= BodyDuration;
		}

		if (m_BodyFrm == m_BodyMaxFrm)
			m_BodyFrm = 0;
	}
	
	
}

void CAnimUI::Render_DerivedUI()
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	Vec2 vCenter = vPos + vScale / 2.f;

	SELECT_BRUSH(BackDC, BRUSH_TYPE::BLACK);

	Rectangle(BackDC
		, (int)(vPos.x)
		, (int)(vPos.y)
		, (int)(vPos.x + vScale.x)
		, (int)(vPos.y + vScale.y));

	
	if (m_Bang)
	{
		BLENDFUNCTION blend{};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		Vec2 Offset = m_Bang->GetFrm(m_BangFrm).Offset;
		int Width = m_Bang->GetFrm(m_BangFrm).Texture->GetWidth();
 		int Height = m_Bang->GetFrm(m_BangFrm).Texture->GetHeight();

		AlphaBlend(BackDC
			, (int)(vCenter.x - Width / 2.f + Offset.x)
			, (int)(vCenter.y - Height / 2.f + Offset.y)
			, Width, Height
			, m_Bang->GetFrm(m_BangFrm).Texture->GetDC()
			, 0, 0
			, Width, Height
			, blend);
	}

	if (m_Body)
	{
		BLENDFUNCTION blend{};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		Vec2 Offset = m_Body->GetFrm(m_BodyFrm).Offset;
		int Width = m_Body->GetFrm(m_BodyFrm).Texture->GetWidth();
		int Height = m_Body->GetFrm(m_BodyFrm).Texture->GetHeight();

		AlphaBlend(BackDC
			, (int)(vCenter.x - Width / 2.f + Offset.x)
			, (int)(vCenter.y - Height / 2.f + Offset.y)
			, Width, Height
			, m_Body->GetFrm(m_BodyFrm).Texture->GetDC()
			, 0, 0
			, Width, Height
			, blend);
	}
	
}
