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
	std::string tilePath = sceneMap->tileSet;
	BitMapPack tileBitMap = ResourceManager::Instance()->LoadBitMap(tilePath, true);

	int tilesWide = tileBitMap.width / TILE_WIDTH;
	int tilesHigh = tileBitMap.height / TILE_WIDTH;
	Log("Height : " + std::to_string(tilesHigh) + " Width : " + std::to_string(tilesWide), DEBUG);
	Log("Height : " + std::to_string(tileBitMap.height) + " Width : " + std::to_string(tileBitMap.width), DEBUG);
	for (auto MapRow : sceneMap->mapTileData)
	{
		for (std::string::size_type Ycounter = 0; Ycounter < MapRow.length(); Ycounter++)
		{
			try {
				// THIS IS DISTURBING
				int index = (int)sceneMap->mapTileData[Xcounter][Ycounter] - 65;
				
				BitMapPack indexBitMap;
				indexBitMap.texture = tileBitMap.texture;
				indexBitMap.width = TILE_WIDTH;
				indexBitMap.height = TILE_WIDTH;

				// GET THE INDEX OF THE TILE IN THE SPRITESHEET
				SDL_Rect* indexRect = new SDL_Rect();
				int xIndex = ((index * TILE_WIDTH) % tileBitMap.width) / TILE_WIDTH;
				int yIndex = ((TILE_WIDTH * index) / tileBitMap.width);

				Log("Char : " + std::to_string(sceneMap->mapTileData[Xcounter][Ycounter]) + " Index : " + std::to_string(index) + " xIndex: " + std::to_string(xIndex) + " yIndex: " + std::to_string(yIndex), DEBUG);

				indexRect->x = xIndex * TILE_WIDTH;
				indexRect->y = yIndex * TILE_WIDTH;
				indexRect->w = TILE_WIDTH;
				indexRect->h = TILE_WIDTH;

				Renderer::Instance()->Draw(indexBitMap, 0 + (Ycounter * TILE_WIDTH), 0 + (Xcounter * TILE_WIDTH), indexRect);
			}
			catch (int e)
			{
				Log("Error loading map. Tile not an integer. X: " + std::to_string(Xcounter) + " Y: " + std::to_string(Ycounter) + " \n" + std::to_string(e), ERROR);
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
	drawBitMap = ResourceManager::Instance()->LoadBitMap(DEFAULT_TILE_PATH, true);

	sceneMap->tileSet = "../Sprites/defaultTiles.bmp";
}