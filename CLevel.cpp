#include "pch.h"
#include "CLevel.h"

#include "CEngine.h"

#include "CObj.h"
#include "CTexture.h"


CLevel::CLevel()
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


void CLevel::Save()
{

}

void CLevel::Load()
{

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

	Tick_Derived();
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
	for (auto& Layer : m_ArrLayerObj)
	{
		for (auto& obj : Layer)
		{
			obj->Render();
		}
	}

	Render_Derived();
}

