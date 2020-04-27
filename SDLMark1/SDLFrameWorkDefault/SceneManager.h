#pragma once

#include "Scene.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>

#include "Components.h"

class SceneManager
{
private:

	static SceneManager* sInstance; /*!< Static instance of the SceneManager class. */

	std::vector<Scene*> mScenesInBuild; /*!< A vector of Scenes that are in the game.*/
	std::unordered_map<std::string, Scene*> loadedScenes; /*!< A hash map of the scenes which have been loaded, to save on load time.*/
	Scene* currentScene; /*!< Reference to the current Scene.*/

	int mNextBuildIndex; /*!< Int for what the next build index is when adding scenes to the build list.*/

	Event* eventStore; /*!< The event being processed this frame.*/

public:

	/*!
		Method for getting an instance of SceneManager.
	*/
	static SceneManager* Instance();

	/*!
		Gets the next build index.
		\return The next build index.
	*/
	int GetNextBuildIndex();

	/*!
		Adds a scene to the build list.
		\param[in] reference to the scene to add to the build.
	*/
	void AddSceneToBuild(Scene* scene);

	/*!
		Load a scene by sceneName,
		\param[in] sceneName The name of the scene to load,
	*/
	void LoadScene(std::string sceneName);

	/*!
		Load a scene by build index,
		\param[in] buildIndex The build index of the scene to load,
	*/
	void LoadScene(int buildIndex);

	/*!
		Load a scene by file path.
		\param[in] path The file path of the scene, including scene file. e.g: ../Assets/Scenes/Level1.filthyscene .
	*/
	void LoadSceneByPath(std::string path);

	/*!
		Load a scene by file path, but DOES NOT save the previous scene!.
		When transitioning from one scene to the next in-game, you don't want to save all the dead enemies in the last scene to disk.
		\param[in] path The file path of the scene, including scene file. e.g: ../Assets/Scenes/Level1.filthyscene .
	*/
	void LoadSceneByPathNoSave(std::string path);

	/*!
		Load a scene by sceneName, but DOES NOT save the previous scene!.
		When transitioning from one scene to the next in-game, you don't want to save all the dead enemies in the last scene to disk.
		\param[in] path The name of the scene.
	*/
	void LoadSceneNoSave(std::string sceneName);

	/*!
		Saves the current scene, and reloads it to apply changes.
	*/
	void SaveScene();

	/*!
		Returns a reference to the current scene.
		\return A reference to the current scene.
	*/
	Scene* getCurrentScene();

	/*
		Tick checks for events from eventSystem and processes them if it finds one.
	*/
	void Tick();

private:

	/*
		The base loadScene function which loads a scene from a reference to a scene. All load scene functions come back to this.
		The exception is the LoadSceneNoSave functions which do it themselves as this function also saves the previous scene.

		\param scene The scene to load.
	*/
	void LoadScene(Scene* scene);

	SceneManager();
	~SceneManager();
};