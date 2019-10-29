#pragma once
#include "SDL.h"
struct BitMapPack
{
	SDL_Texture* texture;
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

typedef enum WindowEvents
{
	WinEvent_QUIT=1,
};

enum ComponentMask
{
	COMPONENT_Position =		0b0000000000000001,
	COMPONENT_Velocity =		0b0000000000000010,
	COMPONENT_Sprite   =		0b0000000000000100,
};