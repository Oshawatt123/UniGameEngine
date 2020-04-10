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

	Vector2 gameCamera;
	int SW, SH;

	PhysicsEngine* pe;

	bool needToStart;

public:

	Scene(PhysicsEngine* PE, int screen_width, int screen_height);
	Scene(std::string name, PhysicsEngine* PE, int screen_width, int screen_height);
	~Scene();

	void Reload();

	// updates every component except for rendering
	void Tick();
	void EditorTick();
	// updates all the sprite components and renders the tilemap
	void Draw();

	void AddEntity(Entity* const EntityToAdd);
	void RemoveEntity(Entity* const EntityToRemove);

	std::string GetName();

	Entity* PopulateHeirarchy();

	Entity* getEntityByName(std::string name);

	bool CheckPointCollideEntityScreenSpace(Vector2 point, Entity*& outEntity);

	std::string generateSaveData();

private:

	void SceneInit();
};