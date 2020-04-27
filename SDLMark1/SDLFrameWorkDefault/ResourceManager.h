#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>

#include "rapidxml_utils.hpp"


#include "SDL.h"
#include "EngineStructs.h"
#include "PhysicsEngine.h"
#include "Logger.h"
#include "ECS.h"
#include "Map.h"

#define ASSETS "../Assets"

struct SDL_Surface;
struct SDL_Texture;
struct SDL_Renderer;

// forward declaration is NECESSARY in order to 
class PositionComponent;
class SpriteComponent;
class CharacterController;
class CollisionComponent;
class CameraComponent;
class EnemyControl;
class StairControl;

/*!
	The Resouce Manager is responsible for almost all of the resources used by the game.
	It prevents the loading of textures that have already been loaded.
	It also loads Maps and Scenes.
	Loading the same scene twice is handled by SceneManager.
	Audio is handled by the AudioManager.
*/
class ResourceManager
{

private:
	static ResourceManager* sInstance; /*!< Static instance of the ResourceManager class. */

	std::ifstream inFile; /*!< A stack allocated std::ifstream to save on memory allocations when loading new files.*/

	
	SDL_Renderer* m_pRenderer; /*!< A reference to the renderer.*/

	std::unordered_map<std::string, BitMapPack> m_textureHashMap; /*!< The hash map where all game textures are stored.*/

public:

	/*!
		Loads a bit map from a file. Prevents loading the same bit map twice by checking if it has already been loaded into the texture hash map.
		
		\param[in] filePath The file path of the bitmap you want to load, including filename.
		\param[in] transparency Whether or not the bitmap file uses transparency. Transparency value is (255, 0, 255, 255) or magenta.

		\return The BitMapPack that has been loaded either from file or from the texture hash map.
	*/
	BitMapPack LoadBitMap(std::string filePath, bool transparency);


	/*!
		A function used by the Inspector to check if a file path can be loaded.

		\param[in] filePath The file path to test loading.

		\return Whether or not the given file path can be loaded.
	*/
	bool testLoad(std::string filePath);

	/*!
		Loads a map from a given filePath.

		\param[in] filePath The file path of the map.

		\return A vector of strings representing the map.
	*/
	std::vector<std::string> LoadMap(std::string filePath);

	/*!
		Method for getting an instance of ResourceManager.
	*/
	static ResourceManager* Instance();

	/*!
		Method for getting an instance of ResourceManager.
		\note This MUST be called before any call to Instance() as the ResourceManager has be to initialized with a Renderer.
	*/
	static ResourceManager* Instance(SDL_Renderer* renderer);

	/*!
		Cleans up the Instance of all the pointers it holds on to.
		Specifically, the texture hash map has lots of pointers to MBs of data.
	*/
	void release();

private:

	/*!
		A QoL function that checks if the audioHashMap has a certain key.
		\param[in] key The key to search for
		\return Whether or not the key was found in the audioHashMap.
	*/
	bool checkHashMap(std::string key);

	/*!
		Constructs a Resource Manager with a renderer.
	*/
	ResourceManager(SDL_Renderer* renderer);
	~ResourceManager();
};