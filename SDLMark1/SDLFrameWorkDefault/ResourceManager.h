#pragma once
#include <string>
#include <iostream>
#include <unordered_map>
#include "SDL.h"
#include "EngineStructs.h"

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

class ResourceManager
{

private:
	static ResourceManager* sInstance;

	SDL_Surface* m_pBitMapTempSurface;
	SDL_Texture* m_pBitMapTempTexture;
	SDL_Renderer* m_pRenderer;

	std::unordered_map<std::string, BitMapPack> m_textureHashMap;

public:
	// should this and all member variables be static?
	BitMapPack Load(std::string filePath, bool transparency);

	static ResourceManager* Instance();
	static ResourceManager* Instance(SDL_Renderer* renderer);

private:
	bool checkHashMap(std::string key);

	ResourceManager(SDL_Renderer* renderer);
	~ResourceManager();
};