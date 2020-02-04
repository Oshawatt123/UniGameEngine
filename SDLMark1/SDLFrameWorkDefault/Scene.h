#pragma once
#include <string>
#include <vector>

#include "ECS.h"
#include "Components.h"
#include "Map.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "EngineStructs.h"
#include "PhysicsEngine.h"

#include "rapidxml_utils.hpp"

class Scene
{
private:
	std::string SceneName;
	int SceneBuildNumber;

	Map* sceneMap;

	std::vector<Entity*> EntityList;

	BitMapPack tileBitMap;
	BitMapPack indexBitMap;

	int Xcounter;

	SDL_Rect* indexRect;
	int index;

	int yIndex;
	int xIndex;

	SDL_Rect* camera;

public:

	Scene(PhysicsEngine* PE, SDL_Rect* camera);
	Scene(std::string name, PhysicsEngine* PE, SDL_Rect* camera);

	void Draw();

	void AddEntity( Entity* const EntityToAdd);

private:
	~Scene();

	void SceneInit(PhysicsEngine* PE);
};