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
	std::vector<Entity*> renderables;

	BitMapPack tileBitMap;
	BitMapPack indexBitMap;

	int Xcounter;

	SDL_Rect* indexRect;
	int index;

	int yIndex;
	int xIndex;

	SDL_Rect* camera;
	int SW, SH;

public:

	Scene(PhysicsEngine* PE, SDL_Rect* camera, int screen_width, int screen_height);
	Scene(std::string name, PhysicsEngine* PE, SDL_Rect* camera, int screen_width, int screen_height);

	// updates every component except for rendering
	void Tick();
	// updates all the sprite components and renders the tilemap
	void Draw();

	void AddEntity(Entity* const EntityToAdd);

	std::string GetName();

	void PopulateHeirarchy();

	Entity* getEntityByName(std::string name);

private:
	~Scene();

	void SceneInit(PhysicsEngine* PE);
};