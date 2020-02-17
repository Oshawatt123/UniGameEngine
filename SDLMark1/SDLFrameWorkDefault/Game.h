#pragma once

#ifndef GAME_H
 #define GAME_H


#include "imgui.h"
#include "imgui_sdl.h"

#include <SDL.h>
#include <GL/gl3w.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <memory>

#define RENDER_DEBUG

#include "Renderer.h"
#include "ResourceManager.h"
#include "PhysicsEngine.h"
#include "InputManager.h"
#include "EngineStructs.h"
#include "Scene.h"
#include "Components.h"

class Game
{
private:

	//SDL Jazz
	SDL_Window* m_Window;

	const int SCREEN_WIDTH = 1920;
	const int SCREEN_HEIGHT = 1080;

	const int RENDER_VIEW_WIDTH = SCREEN_WIDTH * 0.5f;
	const int RENDER_VIEW_HEIGHT = SCREEN_HEIGHT * 0.65f;

	const int LEVEL_WIDTH = 1024;
	const int LEVEL_HEIGHT = 768;

	//My Own Jazz
	PhysicsEngine* physicsEngine;

	SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	SDL_Rect renderCamera;

	// PLACEHOLDER SCENE
	Scene* Level1;

	ImGuiIO io;


	// Editor
	bool EditMode = false;
	Entity* currentSelectedEntity;

public:
	Game();
	~Game();

	bool Tick(void);

private:
	void UpdateRenderer(void);
	void UpdateInputManager(void);

	void DrawHeirarchy();
};

#endif