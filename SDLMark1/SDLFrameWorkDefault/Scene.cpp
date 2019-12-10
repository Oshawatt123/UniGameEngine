#include "Scene.h"

Scene::Scene()
{
	SceneBuildNumber = 0;
	SceneName = "DefaultSceneName";

	SceneInit();
}

Scene::Scene(std::string name)
{
	SceneBuildNumber = 0;
	SceneName = name;

	SceneInit();
}

void Scene::Draw()
{

	//draw the map

	int Xcounter = 0;
	for (auto MapRow : sceneMap->mapTileData)
	{
		for (std::string::size_type Ycounter = 0; Ycounter < MapRow.length()-1; Ycounter++)
		{
			if (sceneMap->mapTileData[Xcounter][Ycounter] == (char)35)
			{
				Renderer::Instance()->Draw(ResourceManager::Instance()->LoadBitMap(DEFAULT_TILE_PATH, true), 0 + Ycounter * 64, 0 + Xcounter * 64);
			}
		}
		Xcounter++;
	}

	// Draw sprite for every Entity with sprite Component
	for (auto x : EntityList)
	{
		if ((x->m_GetComponentMask() & COMPONENT_Sprite) == COMPONENT_Sprite)
		{
			Renderer::Instance()->Draw(x->m_ObjectBitMapPack, x->m_position.x, x->m_position.y);
		}
	}
}

void Scene::AddEntity(GameObject* EntityToAdd)
{
	EntityList.push_back(EntityToAdd);
}

Scene::~Scene()
{
}

void Scene::SceneInit()
{
	// load map
	sceneMap = new Map();
	sceneMap->mapTileData = ResourceManager::Instance()->LoadMap("../Maps/map1.txt");
}
