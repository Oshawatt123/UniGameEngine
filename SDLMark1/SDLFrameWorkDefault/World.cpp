#include "World.h"

std::vector<GameObject> World::GetEntityList()
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

void World::AddEntity(GameObject EntityToAdd)
{
	EntityList.push_back(EntityToAdd);
}

World::World()
{
}

World::~World()
{
}
