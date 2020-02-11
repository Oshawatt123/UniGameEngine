#pragma once
#include "SDL.h"
#include <string>

// DEBUG DEFINES
/*
	expand this to have debug macros I can #define for each system
	so they can be turned on and off when I want certain systems to show debug
	also upgrade logger to work off off these macros and a bitset for greater flexibilty
*/
//#define RENDER_DEBUG
//#define XML_DEBUG // not implemented

// REALLY USEFUL MACROS
#define Log(string, verbosity) Logger::Instance()->LogString(string, verbosity)
const int TILE_WIDTH = 32;

// FILE PATH MACROS
const std::string DEFAULT_TILE_PATH = "..Assets/Sprites/Floor_Placeholder.bmp";

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
	Window
};

enum WindowEvents
{
	WinEvent_QUIT=1
};

enum ComponentType
{
	COMPONENT_BASE,
	COMPONENT_TRANSFORM,
	COMPONENT_SPRITE
};

enum Verbosity
{
	EVERYONE,
	FILTHY_DEBUG,
	DEBUG,
	WARNING,
	DBERROR,
	NOTHING
};