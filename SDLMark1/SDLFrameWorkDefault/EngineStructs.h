#pragma once
#include "SDL.h"
struct BitMapPack
{
	SDL_Texture* texture;
	int width;
	int height;
};

struct EventInfo
{
	int EventType;
	int EventData;
};

enum MyEventTypes
{
	KeyboardDown,
	KeyboardUp,
	Window,
};