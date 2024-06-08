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

	END,
};

enum class LEVEL_TYPE
{
	START,
	EDITOR,
	LEVEL_01,
	LEVEL_02,

	END,
};

enum class LAYER_TYPE
{
	BACKGROUND,
	PLAYER,
	TILE,
	PLATFORM,

	END = 32,
};

enum class DEBUG_SHAPE
{
	RECTANGLE,
	ELLIPSE,
	LINE,
};
