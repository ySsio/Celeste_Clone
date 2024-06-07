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

enum class GROUP_TYPE
{
	BACKGROUND,
	PLAYER,
	MONSTER,
	TILE,
	PLAYER_PROJECTILE,
	MONSTER_PROJECTILE,

	END,
};