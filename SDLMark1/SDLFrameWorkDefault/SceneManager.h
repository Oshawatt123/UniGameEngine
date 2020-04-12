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

	static SceneManager* sInstance;

	std::vector<Scene*> mScenesInBuild;
	std::unordered_map<std::string, Scene*> loadedScenes;
	Scene* currentScene;

	int mNextBuildIndex;

	Event* eventStore;

public:

	static SceneManager* Instance();

	int GetNextBuildIndex();

	void AddSceneToBuild(Scene* scene);

	void LoadScene(std::string sceneName);
	void LoadScene(int buildIndex);
	void LoadSceneByPath(std::string path);

	void SaveScene();

	Scene* getCurrentScene();

	void Tick();

private:

	void LoadScene(Scene* scene);

	SceneManager();
	~SceneManager();
};