#include "Scene.h"

Scene::Scene()
{
	SceneBuildNumber = 0;
	SceneName = "DefaultSceneName";
}

Scene::Scene(std::string name)
{
	SceneBuildNumber = 0;
	SceneName = name;
}

std::vector<GameObject*> Scene::GetEntityList()
{
	return EntityList;
}

void Scene::AddEntity(GameObject* EntityToAdd)
{
	EntityList.push_back(EntityToAdd);
}

Scene::~Scene()
{
}