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
void Release_Map(map<T1, T2*>& _map)
{
	for (auto inst : _map)
	{
		if (inst.second == nullptr) continue;
		delete inst.second;
	}

	_map.clear();
}

template <typename T1, typename T2>
void Release_HashMap(unordered_map<T1, T2*>& _map)
{
	for (auto inst : _map)
	{
		if (inst.second == nullptr) continue;
		delete inst.second;
	}

	_map.clear();
}

// Game
void Pause_Game();
void Release_Game();

// Task
void Change_Level(LEVEL_TYPE _Type);

void Reset_Level();

void Move_Room(int _Room);

void Add_Object(CObj* _Obj, LAYER_TYPE _Type);

void Delete_Object(CObj* _Obj);

// Debug Render
#ifdef _DEBUG
void Debug_Render(DEBUG_SHAPE _Shape, PEN_TYPE _Pen, BRUSH_TYPE _Brush, Vec2 _Pos, Vec2 _Scale, float _Duration = 0.f);
#endif

// Camera
Vec2 GetRenderPosFromCam(Vec2 _Pos);


// Bitmap Control

// 잔상 만들기 위한 함수
void FillAlphaNonZeroAreas(HBITMAP hBitmap, COLORREF rgba);

// Easing Function
Vec2 cubicBezier(Vec2 P0, Vec2 P1, Vec2 P2, Vec2 P3, float t);

float easeInOut(float t);