#pragma once
#include <vector>

#include "GameObject.h"

class World
{

private:
	static World* sInstance;

	static std::vector<GameObject> EntityList;

public:
	std::vector<GameObject> GetEntityList();

	static World* Instance();

	static void AddEntity(GameObject EntityToAdd);

private:
	World();
	~World();
};