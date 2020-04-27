#pragma once
#include "SDL.h"
#include <string>

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
#define filthyRenderer Renderer::Instance()
#define filthyAudio AudioManager::Instance()
#define Physics PhysicsEngine::Instance()


const int TILE_WIDTH = 16;

// FILE PATH MACROS
const std::string DEFAULT_TILE_PATH = "..Assets/Sprites/Floor_Placeholder.bmp";
const std::string DEFAULT_ROOT = "../Assets/";

// ImGui flags
//static ImGuiTreeNodeFlags heirarchyFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
//static ImGuiTreeNodeFlags fileViewerFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

static const float f_zero =	 0.0f;
static const float f_min =	-10000;
static const float f_max =   10000;

/*!
	BitMapPack is a storage class for textures, and their attributes.
	It exists to make passing textures around easier, as it eliminates the need to also pass the width and height as extra parameters just taking up space.
	This also exists because SDL_Texture does not contain a definition for width and height. That data is stored on the SDL_Surface, which is deleted as soon as the asset is loaded. Hence making it a wise idea to grab this data when the image is first loaded and the surface generated.
*/
struct BitMapPack
{
	SDL_Texture* texture = nullptr; /*!< The texture of the BitMap.*/
	int width;						/*!< The width of the texture.*/
	int height;						/*!< The height of the texture*/
};

/*!
	AudioPack is much like BitMapPack since it is a storage class for Audiofiles and they're attributes.
	There is no need to have functions require so many parameters, so everything necessary is stored in this struct.
*/
struct AudioPack
{
	SDL_AudioSpec wavSpec;		/*!< The SDL_AudioSpec needed by SDL.*/
	Uint32 wavLength;			/*!< The length of the WAV file.*/
	Uint8* wavBuffer;			/*!< The buffer used by SDL when playing the WAV file.*/
	SDL_AudioDeviceID devideID;	/*!< The ID of this sound.*/
};

enum MyEventTypes
{
	KeyUp,
	KeyDown,
	Mouse,
	Window,
	NumEventTypes
};

enum MouseButtons
{
	LMB,
	RMB,
	MMB,
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

enum FilthyEventType
{
	SCENE_LOAD,
};