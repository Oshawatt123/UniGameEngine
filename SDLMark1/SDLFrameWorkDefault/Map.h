#pragma once
#include <string>
#include <vector>
class Map
{
public:
	std::vector<std::string> mapTileData;
	std::vector<std::string> mapCollisionData;
	std::vector<std::string> mapEntityData;

	std::string filePath;

	std::string tileSet;

	Map();
	~Map();
	bool MapLoaded();
};