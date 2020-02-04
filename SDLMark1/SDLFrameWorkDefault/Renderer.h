#pragma once

#include <iostream>

#include "SDL.h"
#include "EngineStructs.h"
#include "Logger.h"

class Renderer
{

public:

private:
	static Renderer* sInstance;

	SDL_Renderer* m_pRenderer;

	SDL_Rect* camera;
	SDL_Rect* renderCamera;

public:
	void Draw(BitMapPack bitMapPack, SDL_Rect* destRect, SDL_Rect* srcRect = NULL);

	void Draw(BitMapPack bitMapPack, int x, int y, SDL_Rect* srcRect = NULL);

	static Renderer* Instance();

	static Renderer* Instance(SDL_Window* Window, SDL_Rect* camera, SDL_Rect* renderCamera);

	SDL_Renderer* getRenderer();

	void UpdateRenderer();

	void ClearRenderer();

private:
	Renderer(SDL_Window* Window);

	~Renderer();
};