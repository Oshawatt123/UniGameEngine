#pragma once
#include "SDL.h"
#include <string>

// DEBUG DEFINES
#define RENDER_DEBUG

// REALLY USEFUL MACROS
#define Log(string, verbosity) Logger::Instance()->LogString(string, verbosity)
#define TILE_WIDTH 32

// FILE PATH MACROS
#define DEFAULT_TILE_PATH "../Sprites/Floor_Placeholder.bmp"

struct BitMapPack
{
	SDL_Texture* texture = nullptr;
	int width;
	int height;
};

enum MyEventTypes
{
	KeyDown,
	KeyUp,
	LeftMouse,
	RightMouse,
	MiddleMouse,
	MouseWheel,
	MouseGesture,
	Window,
};

enum WindowEvents
{
	WinEvent_QUIT=1,
};

enum ComponentMask
{
	COMPONENT_CharacterControl =		0b0000000000000001,
	COMPONENT_Sprite   =				0b0000000000000010,
	COMPONENT_Collidable =				0b0000000000000100,
};

enum Verbosity
{
	EVERYONE,
	ERROR,
	DEBUG,
	NOTHING,
};