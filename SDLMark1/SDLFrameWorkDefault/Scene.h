#pragma once
#include <string>
#include <vector>

#include "GameObject.h"

class Scene
{
private:
	std::string SceneName;
	int SceneBuildNumber;

	// Map* sceneMap;

	std::vector<GameObject*> EntityList;

public:

	Scene();
	Scene(std::string name);

	std::vector<GameObject*> GetEntityList();

	void AddEntity(GameObject* EntityToAdd);

private:
	~Scene();
};

