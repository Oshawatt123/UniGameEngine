#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>

#include "rapidxml_utils.hpp"


#include "SDL.h"
#include "EngineStructs.h"
#include "PhysicsEngine.h"
#include "Logger.h"
#include "ECS.h"
#include "Map.h"

#define ASSETS "../Assets"

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

class PositionComponent;
class SpriteComponent;
class CharacterController;
class CollisionComponent;
class CameraComponent;
class EnemyControl;
class StairControl;

class ResourceManager
{

private:
	static ResourceManager* sInstance;

	std::ifstream inFile;

	
	SDL_Renderer* m_pRenderer;
	PhysicsEngine* pe;

	std::unordered_map<std::string, BitMapPack> m_textureHashMap;
	//std::unordered_map<std::string, Scene> m_sceneHashMap;

public:
	// should this and all member variables be static? NO
	// do not static member variables. there is no point
	BitMapPack LoadBitMap(std::string filePath, bool transparency);

	bool testLoad(std::string filePath);

	//Scene* LoadScene(std::string filePath);
	std::vector<std::string> LoadMap(std::string filePath);

	static ResourceManager* Instance();
	static ResourceManager* Instance(SDL_Renderer* renderer, PhysicsEngine* _pe);

	std::vector<Entity*> LoadScene(Map& outMap, std::string sceneName);

	void release();

private:
	bool checkHashMap(std::string key);

	ResourceManager(SDL_Renderer* renderer, PhysicsEngine* _pe);
	~ResourceManager();
};