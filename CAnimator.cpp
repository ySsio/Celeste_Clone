#include "pch.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CTimeMgr.h"
#include "CObj.h"
#include "CTexture.h"
#include "CEngine.h"

CAnimator::CAnimator()
	: m_CurAnim(nullptr)
	, m_AccTime(0.f)
	, m_CurIdx(0)
	, m_FrmCnt(0)
	, m_Repeat(true)
	, m_Done(false)
{
}

CAnimator::~CAnimator()
{
}

void CAnimator::Play(const wstring& _AnimName, bool _Repeat)
{
	m_CurAnim = m_MapAnim.find(_AnimName)->second;
	m_CurIdx = 0;
	m_FrmCnt = m_CurAnim->GetFrmCount();
	m_Repeat = _Repeat;
	m_AccTime = 0.f;
	m_Done = false;
}

void CAnimator::Pause()
{
	m_CurAnim = nullptr;
	m_AccTime = 0.f;
	m_Done = true;
}

void CAnimator::FinalTick()
{
	if (!m_CurAnim)
		return;

	m_AccTime += fDT;

	float curDuration = m_CurAnim->GetFrm(m_CurIdx).Duration;
	if (m_AccTime >= curDuration)
	{
		m_AccTime -= curDuration;
		++m_CurIdx;

		if (m_CurIdx == m_FrmCnt)
		{
			if (m_Repeat)
				m_CurIdx = 0;
			else
			{
				m_Done = true;
				m_CurAnim = nullptr;
				m_CurIdx = 0;
				m_AccTime = 0.f;
			}
		}
	}

}

void CAnimator::Render()
{
	Render(BackDC);
}

void CAnimator::Render(HDC _DC, bool _Player)
{
	if (m_Done)
		return;

	const tAnimFrm& curFrm = m_CurAnim->GetFrm(m_CurIdx);
	UINT Width = curFrm.Texture->GetWidth();
	UINT Height = curFrm.Texture->GetHeight();

	Vec2 vPos = GetOwner()->GetRenderPos();
	vPos += curFrm.Offset;

	BLENDFUNCTION blend{};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	int _x = (int)(vPos.x - Width / 2.f);
	int _y = (int)(vPos.y - Height / 2.f);


	if (_Player)
	{
		_x = (int)(curFrm.Offset.x - Width / 2.f + BODY_SCALE/2.f);
		_y = (int)(curFrm.Offset.y - Height / 2.f + BODY_SCALE/2.f);
	}

	AlphaBlend(_DC
		, _x, _y
		, Width, Height
		, curFrm.Texture->GetDC()
		, 0, 0
		, Width, Height
		, blend);
	
}
