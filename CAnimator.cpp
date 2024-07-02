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
	if (m_Done)
		return;

	Vec2 vPos = GetOwner()->GetRenderPos();
	const tAnimFrm& curFrm = m_CurAnim->GetFrm(m_CurIdx);
	UINT Width = curFrm.Texture->GetWidth();
	UINT Height = curFrm.Texture->GetHeight();
	vPos += curFrm.Offset;

	BLENDFUNCTION blend{};
	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = 255;
	blend.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(BackDC
		, (int)(vPos.x - Width / 2.f)
		, (int)(vPos.y - Height / 2.f)
		, Width, Height
		, curFrm.Texture->GetDC()
		, 0, 0
		, Width, Height
		, blend);
	
}
