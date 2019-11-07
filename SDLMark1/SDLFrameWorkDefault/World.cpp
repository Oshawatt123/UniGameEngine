#include "World.h"

World* World::sInstance = NULL;
std::vector<GameObject*> World::EntityList;

std::vector<GameObject*> World::GetEntityList()
{
	return EntityList;
}

World* World::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new World();
	}

	return sInstance;
}

void World::AddEntity(GameObject* EntityToAdd)
{
	EntityList.push_back(EntityToAdd);
}

World::World()
{
}

World::~World()
{
}