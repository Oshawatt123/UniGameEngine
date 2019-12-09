#pragma once

#include "Scene.h"

#include <string>
#include <vector>

class SceneManager
{
private:

	static SceneManager* sInstance;

	std::vector<Scene*> mScenesInBuild;
	Scene* currentScene;

	int mNextBuildIndex;

public:

	static SceneManager* Instance();

	int GetNextBuildIndex();

	void AddSceneToBuild(Scene* scene);

	void LoadScene(std::string sceneName);
	void LoadScene(int buildIndex);

private:

	void LoadScene(Scene* scene);

	SceneManager();
	~SceneManager();
};