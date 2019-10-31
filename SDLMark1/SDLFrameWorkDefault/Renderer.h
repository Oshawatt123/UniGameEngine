#pragma once

#include <iostream>

#include "SDL.h"
#include "EngineStructs.h"

class Renderer
{

public:
	static SDL_Renderer* m_pRenderer;
private:
	static Renderer* sInstance;

public:
	static void Draw(BitMapPack bitMapPack, SDL_Rect* destRect);

	static Renderer* Instance();

	static Renderer* Instance(SDL_Window* Window);

private:
	Renderer(SDL_Window* Window);

	~Renderer();
};