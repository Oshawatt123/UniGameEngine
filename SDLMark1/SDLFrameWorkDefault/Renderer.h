#pragma once

#include <iostream>

#include "SDL.h"
#include "EngineStructs.h"

class Renderer
{

public:

private:
	static Renderer* sInstance;

	SDL_Renderer* m_pRenderer;

public:
	void Draw(BitMapPack bitMapPack, SDL_Rect* destRect);

	static Renderer* Instance();

	static Renderer* Instance(SDL_Window* Window);

	SDL_Renderer* getRenderer();

private:
	Renderer(SDL_Window* Window);

	~Renderer();
};