#pragma once
#include <string>
#include <vector>

#include "GameObject.h"
#include "Map.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "EngineStructs.h"

class Scene
{
private:
	std::string SceneName;
	int SceneBuildNumber;

	Map* sceneMap;

	std::vector<GameObject*> EntityList;

	BitMapPack tileBitMap;
	BitMapPack indexBitMap;

	int Xcounter;

	SDL_Rect* indexRect;

	int index;

	int yIndex;
	int xIndex;

public:

	Scene();
	Scene(std::string name);

	void Draw();

	void AddEntity(GameObject* EntityToAdd);

private:
	~Scene();

	void SceneInit();
};

