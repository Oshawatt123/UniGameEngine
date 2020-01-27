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

	// draw the map
	// move the index-finding code into the renderer / resourceManager

	Xcounter = 0;
	tileBitMap = ResourceManager::Instance()->LoadBitMap(sceneMap->tileSet, true);

	for (auto MapRow : sceneMap->mapTileData)
	{
		for (std::string::size_type Ycounter = 0; Ycounter < MapRow.length(); Ycounter++)
		{
			try {
				// THIS IS DISTURBING
				// -65 is because "A" in the map file has an ASCII value of 65, so -65 gives 0; the index we want
				index = (int)sceneMap->mapTileData[Xcounter][Ycounter] - 65;

				indexBitMap.texture = tileBitMap.texture;
				indexBitMap.width = TILE_WIDTH;
				indexBitMap.height = TILE_WIDTH;

				// GET THE INDEX OF THE TILE IN THE SPRITESHEET
				xIndex = ((index * TILE_WIDTH) % tileBitMap.width) / TILE_WIDTH;
				yIndex = ((TILE_WIDTH * index) / tileBitMap.width);

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

	// Update Every GameObject
   	for (auto entity : EntityList)
	{
		entity->Tick();
	}
}

void Scene::AddEntity(Entity* EntityToAdd)
{
	EntityList.push_back(EntityToAdd);
}

Scene::~Scene()
{
	// scene clean-up
	for (auto entity : EntityList)
	{
		delete entity;
		entity = nullptr;
	}
}

void Scene::SceneInit()
{
	// load map
	// needs to be replaced by an actual load

	// load the scene file
	rapidxml::file<> xmlFile("../Assets/Scenes/Level1.xml");
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	std::cout << doc.first_node()->name() << std::endl;

	rapidxml::xml_node<>* entitiesNode = doc.first_node()->first_node();
	std::cout << entitiesNode->name() << std::endl;
	// for each entity under the entities node
	for (rapidxml::xml_node<>* entity = entitiesNode->first_node(); entity;
		entity = entitiesNode->first_node())
	{

		// the first attribute (name tag)
		std::cout << entity->first_attribute()->value() << std::endl;
		Entity* newEntity = new Entity();
		// for every data entry in an entity
		for (rapidxml::xml_node<>* entityData = entity->first_node(); entityData;
			entityData = entity->first_node())
		{
			std::cout << entityData->name() << std::endl;
			if (std::string(entityData->name()) == "component")
			{
				std::cout << entityData->first_attribute()->value() << std::endl;
				if (std::string(entityData->first_attribute()->value()) == "PositionComponent")
				{
					newEntity->addComponent<PositionComponent>();
				}
				if (std::string(entityData->first_attribute()->value()) == "SpriteComponent")
				{
					newEntity->addComponent<SpriteComponent>(entityData->first_node()->first_attribute()->value());
				}
				if (std::string(entityData->first_attribute()->value()) == "CharacterController")
				{
					newEntity->addComponent<CharacterController>();
				}
			}
			else
			{
				std::cout << "Anomoly found, data :" << entityData->first_attribute()->value() << std::endl;
			}

			AddEntity(newEntity);

			entity->remove_first_node();
		}
		entitiesNode->remove_first_node();
	}

	sceneMap = new Map();
	sceneMap->mapTileData = ResourceManager::Instance()->LoadMap("../Maps/map1.txt");

	indexRect = new SDL_Rect();
	if (sceneMap->MapLoaded())
	{
		sceneMap->tileSet = "../Assets/Sprites/defaultTiles.bmp";
	}
	else
	{
		Log("Map Tile Data not loaded", ERROR);
	}
}