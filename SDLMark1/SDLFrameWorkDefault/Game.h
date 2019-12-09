#pragma once

#ifndef GAME_H
 #define GAME_H
#include <SDL.h>
#include <stdio.h>
#include <iostream>

#include "Renderer.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "EngineStructs.h"
#include "Scene.h"

// GAMEOBJECT COMPONENTS
#include "GameObject.h"

class Game
{
private:

	//SDL Jazz
	SDL_Window* m_Window;

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	//Objects!
	GameObject* myGameObject;

	// PLACEHOLDER SCENE
	Scene* Level1;

public:
	Game();
	~Game();

	bool Tick(void);

private:
	void UpdateRenderer(void);
	void UpdateInputManager(void);
};

#endif