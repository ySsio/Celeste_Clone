#include "pch.h"
#include "CLevel.h"

#include "CEngine.h"

#include "CObj.h"
#include "CTexture.h"

CLevel::CLevel()
	: m_BackGround(nullptr)
{
}

CLevel::~CLevel()
{
	for (auto& group : m_ArrGroupObj)
	{
		for (auto& obj : group)
		{
			delete obj;
		}
		group.clear();
	}
}



void CLevel::Exit()
{
}

void CLevel::Tick()
{
	for (auto& group : m_ArrGroupObj)
	{
		for (auto& obj : group)
		{
			obj->Tick();
		}
	}
}

void CLevel::Render(HDC _hDC)
{
	Vec2 vRes = CEngine::Get()->GetResolution();
	if (m_BackGround)
	{
		BLENDFUNCTION blend{};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(_hDC
			, 0, 0
			, vRes.x
			, vRes.y
			, m_BackGround->GetDC()
			, 0, 0
			, m_BackGround->GetWidth()
			, m_BackGround->GetHeight()
			, blend);
	}

	for (auto& group : m_ArrGroupObj)
	{
		for (auto& obj : group)
		{
			obj->Render();
		}
	}
}

