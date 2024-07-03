#pragma once

enum class PEN_TYPE
{
	WHITE,
	BLACK,
	RED,
	GREEN,
	BLUE,
	
	END,
};

enum class BRUSH_TYPE
{
	WHITE,
	BLACK,
	RED,
	GREEN,
	BLUE,
	HOLLOW,
	GRAY,
	COZY_GREEN,

	END,
};

enum class LEVEL_TYPE
{
	START,
	EDITOR,
	EDITOR_ANIM,
	EDITOR_MAP,
	LEVEL_01,
	LEVEL_02,

	END,
};

enum class LAYER_TYPE
{
	BACKGROUND,
	EFFECT,
	PLAYER,
	PLATFORM,
	PARTICLE,

	
	UI = 31,
	END = 32,
};

enum class DEBUG_SHAPE
{
	RECTANGLE,
	ELLIPSE,
	LINE,
};

enum class TASK_TYPE
{
	CREATE_OBJECT,	// wParam : Object Address (CObj*) , lParam : Layer Type (LAYER_TYPE)
	DELETE_OBJECT,	// wParam : Object Address (CObj*)
	CHANGE_LEVEL,	// wParam : Level Address (CLevel*)

};


enum class LOG_LEVEL
{
	LOG,
	WARNING,
	BUG,
};