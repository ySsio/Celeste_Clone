#pragma once

#include "enum.h"
#include "assert.h"

struct Vec2
{
	float x;
	float y;

	Vec2() : x(0.f), y(0.f) {}
	Vec2(float _x, float _y) : x(_x), y(_y) {}

	bool IsZero()
	{
		return x == 0.f && y == 0.f;
	}

	Vec2 operator + (Vec2 _Other)
	{
		return Vec2(x + _Other.x, y + _Other.y);
	}

	Vec2& operator += (Vec2 _Other)
	{
		x += _Other.x;
		y += _Other.y;
		return *this;
	}

	Vec2 operator - (Vec2 _Other)
	{
		return Vec2(x - _Other.x, y - _Other.y);
	}

	Vec2& operator -= (Vec2 _Other)
	{
		x -= _Other.x;
		y -= _Other.y;
		return *this;
	}

	Vec2 operator * (float _f)
	{
		return Vec2(x * _f, y * _f);
	}

	Vec2& operator *= (float _f)
	{
		x *= _f;
		y *= _f;
		return *this;
	}

	Vec2 operator / (float _f)
	{
		assert(_f != 0);
		return Vec2(x / _f, y / _f);
	}

	Vec2& operator /= (float _f)
	{
		assert(_f != 0);
		x /= _f;
		y /= _f;
		return *this;
	}

	float Length()
	{
		return sqrt(x * x + y * y);
	}

	Vec2& Normalize()
	{
		return *this /= Length();
	}

	Vec2 Normalized()
	{
		return *this / Length();
	}
};


struct tDebugShapeInfo
{
	DEBUG_SHAPE		Shape;
	Vec2			Position;
	Vec2			Scale;
	PEN_TYPE		Pen;
	BRUSH_TYPE		Brush;
	float			Duration;
	float			AccTime;	// duration을 체크하기 위한 누적용 변수
};

//struct tLog
//{
//	wstring strLog;
//	float Time;
//	LOG_LEVEL Level;
//};