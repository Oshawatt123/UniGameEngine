#pragma once
#include "SDL.h"
#include <string>

#include "Time.h"

#define ENGINE_EDITOR_MODE

// DEBUG DEFINES
/*
	expand this to have debug macros I can #define for each system
	so they can be turned on and off when I want certain systems to show debug
	also upgrade logger to work off off these macros and/or a bitset for greater flexibilty
*/
//#define RENDER_DEBUG
//#define XML_DEBUG // not implemented

// REALLY USEFUL MACROS
#define Log(string, verbosity) Logger::Instance()->LogString(string, verbosity)
#define blackboard BlackBoard::Instance()
#define filthyTime Time::Instance()
const int TILE_WIDTH = 16;

// FILE PATH MACROS
const std::string DEFAULT_TILE_PATH = "..Assets/Sprites/Floor_Placeholder.bmp";

// ImGui flags
//static ImGuiTreeNodeFlags heirarchyFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
//static ImGuiTreeNodeFlags fileViewerFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

static const float f_zero =	 0.0f;
static const float f_min =	-10000;
static const float f_max =   10000;

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

enum Verbosity
{
	EVERYONE,
	FILTHY_DEBUG,
	DEBUG,
	WARNING,
	DBERROR,
	NOTHING
};