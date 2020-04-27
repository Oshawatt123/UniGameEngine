#include "Map.h"


Map::Map() {}

Map::~Map() {}

bool Map::MapLoaded()
{
	if (mapTileData.size() == 0) // || mapCollisionData.size() == 0 || mapEntityData.size() == 0)
	{
		return false;
	}
	return true;
}
