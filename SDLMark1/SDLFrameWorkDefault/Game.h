#pragma once

#ifndef GAME_H
 #define GAME_H
#include <SDL.h>
#include <stdio.h>
#include <iostream>

class Game
{
private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

public:
	Game();
	~Game();

	void SetDisplayColour(int r, int g, int b);

	void UpdateRenderer(void);
};

#endif