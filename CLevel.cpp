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
	for (auto& Layer : m_ArrLayerObj)
	{
		Release_Vector(Layer);
	}
}

void CLevel::AddObject(CObj* _Obj, LAYER_TYPE _Type)
{
	m_ArrLayerObj[(UINT)_Type].push_back(_Obj); _Obj->SetLayerType(_Type);
}


void CLevel::Exit()
{
	for (auto& Layer : m_ArrLayerObj)
	{
		Release_Vector(Layer);
	}
}



void CLevel::Tick()
{
	for (auto& Layer : m_ArrLayerObj)
	{
		for (auto obj : Layer)
		{
			obj->Tick();
		}
	}
}

void CLevel::FinalTick()
{
	for (auto& Layer : m_ArrLayerObj)
	{
		for (auto iter = Layer.begin(); iter != Layer.end();)
		{
			(*iter)->FinalTick();
			if ((*iter)->IsDead())
			{
				iter = Layer.erase(iter);
				continue;
			}
			++iter;
		}
	}
}

void CLevel::Render()
{
	Vec2 vRes = CEngine::Get()->GetResolution();
	if (m_BackGround)
	{
		BLENDFUNCTION blend{};
		blend.BlendOp = AC_SRC_OVER;
		blend.BlendFlags = 0;
		blend.SourceConstantAlpha = 255;
		blend.AlphaFormat = AC_SRC_ALPHA;

		AlphaBlend(BackDC
			, 0, 0
			, (int)vRes.x
			, (int)vRes.y
			, m_BackGround->GetDC()
			, 0, 0
			, m_BackGround->GetWidth()
			, m_BackGround->GetHeight()
			, blend);
	}

	for (auto& Layer : m_ArrLayerObj)
	{
		for (auto& obj : Layer)
		{
			obj->Render();
		}
	}
}

