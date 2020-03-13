#pragma once

#include "Scene.h"
#include "PhysicsEngine.h"

#include <string>
#include <vector>
#include <unordered_map>

class SceneManager
{
private:

	static SceneManager* sInstance;

	std::vector<Scene*> mScenesInBuild;
	std::unordered_map<std::string, Scene*> loadedScenes;
	Scene* currentScene;

	int mNextBuildIndex;

	PhysicsEngine* pe;
	SDL_Rect* camera;

public:

	static SceneManager* Instance(PhysicsEngine* _pe, SDL_Rect* _camera);

	static SceneManager* Instance();

	int GetNextBuildIndex();

	void AddSceneToBuild(Scene* scene);

	void LoadScene(std::string sceneName);
	void LoadScene(int buildIndex);
	void LoadSceneByPath(std::string path);

	Scene* getCurrentScene();

private:

	void LoadScene(Scene* scene);

	SceneManager();
	~SceneManager();
};