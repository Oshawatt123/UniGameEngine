#pragma once
#include <string>
#include <iostream>
#include "SDL.h"
#include "EngineStructs.h"

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

class ResourceManager
{
public:
	ResourceManager(SDL_Renderer* renderer);
	BitMapPack Load(std::string filePath, bool transparency);
private:
	SDL_Surface* m_pBitMapTempSurface;
	SDL_Texture* m_pBitMapTempTexture;
	SDL_Renderer* m_pRenderer;
};