#pragma once

#include "CComponent.h"

template <typename T>
void Release_Vector(vector<T*>& _vec)
{
	for (auto inst : _vec)
	{
		if (inst == nullptr) continue;
		delete inst;
	}

	_vec.clear();
}

template <typename T1, typename T2>
void Release_Map(unordered_map<T1, T2*>& _map)
{
	for (auto inst : _map)
	{
		if (inst.second == nullptr) continue;
		delete inst.second;
	}

	_map.clear();
}

// Debug Render
void Debug_Render(DEBUG_SHAPE _Shape, PEN_TYPE _Pen, BRUSH_TYPE _Brush, Vec2 _Pos, Vec2 _Scale, float _Duration = 0.f);

void ChangeLevel(LEVEL_TYPE _Type);