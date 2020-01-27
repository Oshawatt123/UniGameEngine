#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_map>


#include "SDL.h"
#include "EngineStructs.h"
#include "Logger.h"


#define ASSETS "../Assets"

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

class ResourceManager
{

private:
	static ResourceManager* sInstance;

	std::ifstream inFile;

	SDL_Surface* m_pBitMapTempSurface;
	SDL_Texture* m_pBitMapTempTexture;
	SDL_Renderer* m_pRenderer;

	std::unordered_map<std::string, BitMapPack> m_textureHashMap;
	//std::unordered_map<std::string, Scene> m_sceneHashMap;

public:
	// should this and all member variables be static? NO
	// do not static member variables. there is no point
	BitMapPack LoadBitMap(std::string filePath, bool transparency);
	//Scene* LoadScene(std::string filePath);
	std::vector<std::string> LoadMap(std::string filePath);

	static ResourceManager* Instance();
	static ResourceManager* Instance(SDL_Renderer* renderer);

private:
	bool checkHashMap(std::string key);

	ResourceManager(SDL_Renderer* renderer);
	~ResourceManager();
};