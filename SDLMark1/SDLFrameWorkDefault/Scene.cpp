#include "Scene.h"

void AddBrace(std::string* data, std::string brace, bool end)
{
	if (!end)
		*data = *data + "<" + brace + ">";
	else
		*data = *data + "</" + brace + ">";
}

Scene::Scene(PhysicsEngine* PE, int screen_width, int screen_height)
{
	SceneBuildNumber = 0;
	SceneName = "DefaultSceneName";
	SW = screen_width;
	SH = screen_height;
	SceneInit(PE);
}

Scene::Scene(std::string name, PhysicsEngine* PE, int screen_width, int screen_height)
{
	SceneBuildNumber = 0;
	SceneName = name;
	SW = screen_width;
	SH = screen_height;
	SceneInit(PE);
}

void Scene::Tick()
{
	for (auto entity : EntityList)
	{
		if (entity->isEnabled())
		{
			entity->Tick();
			// move gameCamera to correct position
			if (entity->hasComponent<CameraComponent>())
			{
				gameCamera.x = entity->getComponent<CameraComponent>().getPosition().x - SW / 2;
				gameCamera.x += entity->getComponent<CameraComponent>().camOffset.x;

				gameCamera.y = entity->getComponent<CameraComponent>().getPosition().y - SH / 2;
				gameCamera.y += entity->getComponent<CameraComponent>().camOffset.y;
			}
		}
	}
}

void Scene::EditorTick()
{
	for (auto entity : EntityList)
	{
		if (entity->isEnabled())
		{
			entity->EditorTick();
		}
	}

	// draw a bunch of lines
#ifdef RENDER_DEBUG
	for (size_t i = 0; i < 100; i++)
	{
		for (size_t j = 0; j < 100; j++)
		{
			Renderer::Instance()->DrawLine(
				i * TILE_WIDTH,
				j * TILE_WIDTH,
				i * TILE_WIDTH,
				j * TILE_WIDTH + 1000);
			Renderer::Instance()->DrawLine(
				i * TILE_WIDTH,
				j * TILE_WIDTH,
				i * TILE_WIDTH + 1000,
				j * TILE_WIDTH);
		}
	}
#endif // REDNER_DEBUG

	
}

void Scene::Draw()
{

	// draw the map
	// move the index-finding code into the renderer / resourceManager
	if (InputManager::Instance()->KeyDown(SDL_SCANCODE_U))
	{
		SH++;
		std::cout << SH << std::endl;
	}
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

				Log("Char : " + std::to_string(sceneMap->mapTileData[Xcounter][Ycounter]) + " Index : " + std::to_string(index) + " xIndex: " + std::to_string(xIndex) + " yIndex: " + std::to_string(yIndex), FILTHY_DEBUG);

				indexRect->x = xIndex * TILE_WIDTH;
				indexRect->y = yIndex * TILE_WIDTH;
				indexRect->w = TILE_WIDTH;
				indexRect->h = TILE_WIDTH;

				Renderer::Instance()->Draw(indexBitMap, 0 + (Ycounter * TILE_WIDTH), 0 + (Xcounter * TILE_WIDTH), indexRect);
			}
			catch (int e)
			{
				Log("Error loading map. Tile not an integer. X: " + std::to_string(Xcounter) + " Y: " + std::to_string(Ycounter) + " \n" + std::to_string(e), DBERROR);
			}
		}
		Xcounter++;
	}

	// Update Every GameObject's sprite component
   	for (auto entity : renderables)
	{
		if (entity->isEnabled())
		{
			entity->getComponent<SpriteComponent>().Tick();
		}
	}
}

void Scene::AddEntity(Entity* const EntityToAdd)
{
	EntityList.push_back(EntityToAdd);
	if (EntityToAdd->hasComponent<SpriteComponent>())
	{
		renderables.push_back(EntityToAdd);
	}
}

void Scene::RemoveEntity(Entity* EntityToRemove)
{
	EntityList.erase(std::remove(EntityList.begin(), EntityList.end(), EntityToRemove), EntityList.end());
}

std::string Scene::GetName()
{
	return SceneName;
}

Entity* Scene::PopulateHeirarchy()
{
	for (auto entity : EntityList)
	{
		std::string labelString = std::to_string(entity->ID) + " " + entity->name;
		if (ImGui::Selectable(labelString.c_str()))
		{
			return entity;
		}
		if (ImGui::BeginPopupContextItem("EntityContextMenu"))
		{
			if (ImGui::Selectable("Delete"))
				RemoveEntity(entity);

			ImGui::EndPopup();
		}
	}
	ImGui::Button("TestEntity");
	return nullptr;
}

Entity* Scene::getEntityByName(std::string name)
{
	for (auto entity : EntityList)
	{
		if (entity->name == name)
		{
			return entity;
		}
	}
	return nullptr;
}

bool Scene::CheckPointCollideEntityScreenSpace(Vector2 point, Entity*& outEntity)
{
	for (auto object : EntityList)
	{
		Vector2 otherPos = object->getComponent<PositionComponent>().getPos();

		// Is Point X to the RIGHT of the object's LEFT edge?
		if (point.x + gameCamera.x > otherPos.x + gameCamera.x)
		{
			// Is Point X to the LEFT of the object's RIGHT edge?
			if (point.x + gameCamera.x < otherPos.x + TILE_WIDTH + gameCamera.x)
			{
				// Is Point Y BELOW the object's TOP edge?
				if (point.y + gameCamera.y > otherPos.y + gameCamera.y)
				{
					// Is Point Y ABOVE the object's BOTTOM edge?
					if (point.y + gameCamera.y < otherPos.y + TILE_WIDTH + gameCamera.y)
					{
						outEntity = object;
						Log("Clicked an entity!", DEBUG);
						Log(outEntity->name.c_str(), DEBUG);
						return true;
					}
				}
			}
		}
	}
	outEntity = nullptr;
	return false;
}

std::string Scene::generateSaveData()
{
	std::string saveData;
	saveData = saveData + "<?xml version=\"1.0\" encoding=\"utf-8\"?>";
	AddBrace(&saveData, "scene", false);

	AddBrace(&saveData, "entities", false);
	for (auto object : EntityList)
	{
		// start writing entity information
		std::string braceData = "entity name = \"" + object->name + "\"";
		AddBrace(&saveData, braceData, false);

		// write entity component information
		for (auto component : object->getComponents())
		{
			std::string componentBraceData = "component type = \"" + component->name + "\"";
			AddBrace(&saveData, componentBraceData, false);

			saveData += component->GetSaveData();

			AddBrace(&saveData, "component", true);
		}
		AddBrace(&saveData, "entity", true);
	}
	AddBrace(&saveData, "entities", true);

	// Add map to save file
	std::string mapBraceData = "map path = \"" + sceneMap->filePath + "\"";
	AddBrace(&saveData, mapBraceData, false);
	AddBrace(&saveData, "map", true);

	AddBrace(&saveData, "scene", true);
	return saveData;
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

void Scene::SceneInit(PhysicsEngine* PE)
{
	// load map
	// needs to be replaced by an actual load function

	Log("#################### [XML DEBUG] #####################", DEBUG);
	// load the scene file
	std::string scenePath = "../Assets/Scenes/" + SceneName + ".filthyscene";
	std::cout << scenePath << std::endl;
	rapidxml::file<> xmlFile(scenePath.c_str());
	// setup rapidXML
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	// set root sceneNode
	rapidxml::xml_node<>* sceneNode = doc.first_node();

	Log(sceneNode->name(), DEBUG);

	// set entities parent Node
	rapidxml::xml_node<>* entitiesNode = sceneNode->first_node();
	Log(entitiesNode->name(), DEBUG);
	// for each entity under the entities node
	for (rapidxml::xml_node<>* entity = entitiesNode->first_node(); entity;
		entity = entitiesNode->first_node())
	{
		std::string logstring = "ENTITYNODE NAME ";
		logstring.append(entity->first_attribute()->value());
		Log(logstring, DEBUG);

		// create the entity
		Entity* newEntity = new Entity();
		newEntity->name = entity->first_attribute()->value();

		// for every data entry in an entity
		for (rapidxml::xml_node<>* entityData = entity->first_node(); entityData;
			entityData = entity->first_node())
		{
			if (std::string(entityData->name()) == "component")
			{
				// check for position component
				if (std::string(entityData->first_attribute()->value()) == "PositionComponent")
				{
					// change this shit to a for loop
					std::cout << "FOR LOOP ME PLEEAASEEEEEE" << std::endl;
					int newEntityX = 0;
					int newEntityY = 0;
					int newEntityScale = 1;
					// try for x position and remove the node if it is there
					if (entityData->first_node("xpos"))
					{
						// convert the value to a string
						// value is a char*, so this needs to be converted to a string
						// and then std::stoi converts this to an integer
						std::string xString = entityData->first_node("xpos")->value();
						newEntityX = std::stoi(xString);

						// debug jazz, will be cleaned with logger upgrade
						std::string logstring = "Entity x position set to ";
						logstring.append(entityData->first_node("xpos")->value());
						Log(logstring, DEBUG);

						// remove this node so we can access the next one
						entityData->remove_first_node();
					}
					else
					{
						Log("Error parsing x position data form scene data : x position set to default 0", WARNING);
					}
					// try for y position and remove the node if it is there
					if (entityData->first_node("ypos"))
					{
						std::string yString = entityData->first_node("ypos")->value();
						newEntityY = std::stoi(yString);

						std::string logstring = "Entity y position set to ";
						logstring.append(entityData->first_node("ypos")->value());
						Log(logstring, DEBUG);
						entityData->remove_first_node();
					}
					else
					{
						Log("Error parsing y position data form scene data : y position set to default 0", WARNING);
					}
					if (entityData->first_node("scale"))
					{
						std::string yString = entityData->first_node("scale")->value();
						newEntityScale = std::stoi(yString);

						std::string logstring = "Entity scale set to ";
						logstring.append(entityData->first_node("scale")->value());
						Log(logstring, DEBUG);
						entityData->remove_first_node();
					}
					else
					{
						Log("Error parsing scale data form scene data : scale set to default 1", WARNING);
						newEntityScale = 1;
					}
					newEntity->addComponent<PositionComponent>(newEntityX, newEntityY, newEntityScale);
				}
				// check for sprite component
				if (std::string(entityData->first_attribute()->value()) == "SpriteComponent")
				{
					newEntity->addComponent<SpriteComponent>(entityData->first_node()->first_node()->value());
				}
				// check for charactercontroller
				if (std::string(entityData->first_attribute()->value()) == "CharacterController")
				{
					newEntity->addComponent<CharacterController>();
				}
				// check for collider, and add it to the physics engine
				if (std::string(entityData->first_attribute()->value()) == "CollisionComponent")
				{
					newEntity->addComponent<CollisionComponent>();
					PE->AddCollidableObject(newEntity);
				}
			}
			else
			{
				std::cout << "Anomaly found, data :" << entityData->first_attribute()->value() << std::endl;
			}

			entity->remove_first_node();
		}
		AddEntity(newEntity);
		entitiesNode->remove_first_node();
	}

	// set map node

	entitiesNode = nullptr;
	sceneNode->remove_first_node();
	// the above needs to happen so we can get the second node, and we must clean up entitiesNode so we
	// avoid a pointer pointing to jazz that doesn't exist anymore
	rapidxml::xml_node<>* mapNode = sceneNode->first_node();


	// load map data into the scene
	sceneMap = new Map();
	sceneMap->mapTileData = ResourceManager::Instance()->LoadMap(mapNode->first_attribute()->value());
	sceneMap->filePath = mapNode->first_attribute()->value();

	indexRect = new SDL_Rect();
	if (sceneMap->MapLoaded())
	{
		Log("Scene Map loaded!", DEBUG);
		sceneMap->tileSet = "../Assets/Sprites/defaultTiles.bmp";
	}
	else
	{
		Log("Map Tile Data not loaded", DBERROR);
	}
}