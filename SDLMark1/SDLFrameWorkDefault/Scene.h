#pragma once
#include <string>
#include <vector>

#include "ECS.h"
#include "Map.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "EngineStructs.h"

#include "Components.h"
/*!
	A scene is defined as a collection of Entity 's, and a Map.
*/
class Scene
{
private:
	std::string SceneName; /*!< The name given to a scene, used in some load functions. */

	/*!	
		The build number, to be used in some load functions.
		/note This is not yet implemented.
	*/
	int SceneBuildNumber;

	Map* sceneMap; /*!< The map data used by the scene*/

	std::vector<Entity*> EntityList; /*!< A vector of Entity in this scene.*/
	std::vector<Entity*> renderables; /*!< Of the entities in EntityList, these are those which are renderable.
											This saves on checking which entities need to be rendered each frame.
											The vector is calculated in SceneInit.
									  */

	BitMapPack tileBitMap;	/*!< The BitMapPack used by the map, cached here for convenience.*/
	BitMapPack indexBitMap;	/*!< The clipped BitMapPack for the current tile on the map.*/

	int Xcounter;

	SDL_Rect* indexRect;	/*!< The position and size of the clip needed to take out of the TileMap sprite for the current tile being drawn.*/
	int index;

	int yIndex;
	int xIndex;

	Vector2 gameCamera;		/*!< The position of the %game camera. */
	int SW, SH;

	bool needToStart;		/*!< Used to determine if we need to call SceneInit again when loaded.*/

public:
	/*!
		Basic constructor for Scene
		\param[in] screen_width		The width of the screen.
		\param[in] screen_height	The height of the screen.
	*/
	Scene(int screen_width, int screen_height);

	/*!
		Override constructor for Scene
		\param[in] name				The name of the scene.
		\param[in] screen_width		The width of the screen.
		\param[in] screen_height	The height of the screen.
	*/
	Scene(std::string name, int screen_width, int screen_height);
	~Scene();

	/*!
		Reloads the scene. Used in scene saving as we need to re-load the scene after we have saved.
	*/
	void Reload();

	/*!
		Updates every component except for rendering.
	*/
	void Tick();

	/*!
		Like Tick, but runs when the engine is in edit-mode.
		This %tick will run all the entity's %EditorTick function.
	*/
	void EditorTick();

	/*! 
		Updates all the sprite components in renderables and renders the tilemap.
	*/
	void Draw();

	/*!
		Adds an entity to the scene.
		\param[in] EntityToAdd The entity to add into the scene.
	*/
	void AddEntity(Entity* const EntityToAdd);

	/*!
		Removes an entity from the scene.
		\param[in] EntityToRemove The entity to remove from the scene.
	*/
	void RemoveEntity(Entity* const EntityToRemove);

	/*!
		A getter function for the sceneName.
	*/
	std::string GetName();

	/*!
		This populates the heirarchy in the engine with all of the entities in the scene.
		\return If an entity is selected in the heirarchy, the entity is returned so it can be displayed in the Inspector. nullptr if not.
	*/
	Entity* PopulateHeirarchy();

	/*!
		Get a reference to a specific entity by name
		\param[in] name The name of the entity you want to find
		\return If an entity is found, a reference to that entity is returned. nullptr if not.
	*/
	Entity* getEntityByName(std::string name);

	/*!
		This function is used to check if a point in screen space is over an entity.
		\param[in] point		The point in screen space we want to check.
		\param[out] outEntity	The entity that is at this point in screen space.
		\return					Whether or not there was an entity at point.
	*/
	bool CheckPointCollideEntityScreenSpace(Vector2 point, Entity*& outEntity);

	/*!
		This function is used to check if a point in screen space is over a rect.
		\param[in] point		The point in screen space we want to check.
		\param[in] RectStart	The start of the rect we want to check against.
		\param[in] RectEnd		The end of the rect we want to check against.
		\return					Whether or not there was an entity at point
	*/
	bool CheckPointCollideRectScreenSpace(Vector2 point, Vector2 RectStart, Vector2 RectEnd);

	/*!
		Generate the save data for the scene. Loops over all entity and generates all of their save data.
		See entity, component, and a specific like PositionComponent for more information on how save data is generated.

		\note	A LOT of string concatenation happens here so it can be slow.
	*/
	std::string generateSaveData();

private:

	/*!
		Initializes the scene.
		Vectors are cleared and the scene is loaded with LoadScene.
	*/
	void SceneInit();

	/*!
		Loads the scene from an external file! The file is found from the SceneName.

		\warning Function exceeds dedicated stack size. Unsure how to move more data to heap as it utilises RapidXML. On the to-do list.
	*/
	void LoadScene();
};