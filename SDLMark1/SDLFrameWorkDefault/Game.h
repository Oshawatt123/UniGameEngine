#pragma once

#ifndef GAME_H
 #define GAME_H
#include <SDL.h>
#include <stdio.h>
#include <iostream>

#include "Bitmap.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "GameObject.h"
#include "EngineStructs.h"
#include "World.h"
#include "Systems.h"

class Bitmap;

class Game
{
private:

	//SDL Jazz
	SDL_Window* m_Window;

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	//Objects!
	GameObject* myGameObject;

public:
	Game();
	~Game();

	bool Tick(void);

	void SetDisplayColour(int r, int g, int b);

private:
	void UpdateRenderer(void);
	void UpdateInputManager(void);
};

#endif