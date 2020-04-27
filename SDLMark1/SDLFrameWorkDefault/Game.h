#pragma once

#ifndef GAME_H
 #define GAME_H

 // 3rd party includes
#include "imgui.h"
#include "imgui_sdl.h"
#include "imgui_stdlib.h"

#include <SDL.h>
#include <GL/gl3w.h>

// c++ includes
#include <stdio.h>
#include <iostream>
#include <thread>
#include <memory>
#include <filesystem>
#include <bitset>

// filthy includes
#define RENDER_DEBUG

#include "EngineStructs.h"

#include "Renderer.h"
#include "ResourceManager.h"
#include "AudioManager.h"
#include "SceneManager.h"
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

	// IMGui
	ImGuiIO io;


	// Editor
	Entity* currentSelectedEntity;
	bool draggingEntity;

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
	bool sceneSaveOpen = false;
	std::string newScenePath = "";

	// Debug window variables
	bool debugOpen = true;
	float mousex, mousey;

public:
	Game();
	~Game();

	/**
	* The Main tick of the game
	*/
	bool Tick(void);

private:

	/**
	* Updates the Renderer
	*/
	void UpdateRenderer(void);

	/**
	* Updates the Input Manager
	*/
	void UpdateInputManager(void);

	/**
	* Draw the ImGui Heirarchy Window
	*/
	void DrawHeirarchy();

	/**
	* Draw the ImGui Inspector Window
	*/
	void DrawInspector();

	/**
	* Draw the ImGui Scene Picker Window
	*/
	void DrawScenePicker();

	/**
	* Draw the ImGui Engine Debug Window
	*/
	void DrawEngineDebug();

	/**
	* A QoL function to help with generating the ImGui tree for my file heirarchy (Scene Picker)
	*/
	void followFilePath(std::string path);
};

#endif