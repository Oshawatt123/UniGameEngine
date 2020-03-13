#pragma once

#ifndef GAME_H
 #define GAME_H

 // 3rd party includes
#include "imgui.h"
#include "imgui_sdl.h"

#include <SDL.h>
#include <GL/gl3w.h>

// c++ includes
#include <stdio.h>
#include <iostream>
#include <thread>
#include <memory>
#include <filesystem>

// filthy includes
#define RENDER_DEBUG

#include "EngineStructs.h"

#include "Renderer.h"
#include "ResourceManager.h"
#include "PhysicsEngine.h"
#include "InputManager.h"
#include "Scene.h"
#include "Components.h"
#include "Time.h"

class Game
{
private:

	//SDL Jazz
	SDL_Window* m_Window;

	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;

	const int RENDER_VIEW_WIDTH = SCREEN_WIDTH * 0.5f;
	const int RENDER_VIEW_HEIGHT = SCREEN_HEIGHT * 0.65f;


	//My Own Jazz
	PhysicsEngine* physicsEngine;
	Time* _Time;

	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_Rect renderCamera;

	// PLACEHOLDER SCENE
	Scene* Level1;

	ImGuiIO io;


	// Editor
	bool EditMode = true;
	Entity* currentSelectedEntity;

	bool firstToolOpen = true;

	// Heirarchy Variables
	bool heirarchyOpen = true;
	bool treeNodeDoubleClick = false;

	// Inspector Variables
	bool inspectorOpen = true;
	Entity* clickedObject;

	// Scene Picker Variables
	bool scenePickerOpen = true;
	std::string assetsPath = "../Assets/";

	// Debug window variables
	bool debugOpen = true;
	float mousex, mousey;

public:
	Game();
	~Game();

	bool Tick(void);

private:
	void UpdateRenderer(void);
	void UpdateInputManager(void);

	void DrawHeirarchy();
	void DrawInspector();
	void DrawScenePicker();
	void DrawEngineDebug();
};

#endif