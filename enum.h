#pragma once

enum class PEN_TYPE
{
	WHITE,
	BLACK,
	RED,
	GREEN,
	BLUE,
	ORANGE,

	RED_DASH,
	
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

	BANG_BLUE,
	BANG_RED,
	BANG_PINK,

	END,
};

enum class LEVEL_TYPE
{
	START,
	EDITOR,
	EDITOR_ANIM,
	EDITOR_MAP,
	LEVEL_00,			// tutorial
	LEVEL_01,			// Forsaken City
	LEVEL_02,

	END,
};

enum class ROOM_TYPE
{
	ROOM_0,
	ROOM_1,
	ROOM_2,
	ROOM_3,
	ROOM_4,
	ROOM_5,
	ROOM_6,
	ROOM_7,
	ROOM_8,
	ROOM_9,
};

enum class LAYER_TYPE
{
	BACKGROUND,
	PLAYER_EFFECT,
	PLAYER,
	OBJ,
	PLATFORM,
	EFFECT,
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

enum class BANG_COLOR
{
	PINK,
	RED,
	BLUE,
	WHITE,
};

enum class CAM_EFFECT
{
	RESPAWN,
	ROOMMOVE,

	NONE,
};