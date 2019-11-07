#pragma once

#ifndef GAME_H
 #define GAME_H
#include <SDL.h>
#include <stdio.h>
#include <iostream>

<<<<<<< HEAD
class Bitmap;
=======
#include "Renderer.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "EngineStructs.h"
#include "World.h"

// GAMEOBJECT COMPONENTS
#include "GameObject.h"
>>>>>>> InputManager

class Game
{
private:

	//SDL Jazz
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	//Bitmaps!
	Bitmap* m_wood;

public:
	Game();
	~Game();

<<<<<<< HEAD
	void SetDisplayColour(int r, int g, int b);

=======
	bool Tick(void);

private:
>>>>>>> InputManager
	void UpdateRenderer(void);
};

#endif