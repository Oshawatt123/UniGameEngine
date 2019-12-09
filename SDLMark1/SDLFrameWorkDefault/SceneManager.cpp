#include "SceneManager.h"

SceneManager* SceneManager::sInstance = NULL;

SceneManager* SceneManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new SceneManager();
	}
	return sInstance;
}

int SceneManager::GetNextBuildIndex()
{
	return mNextBuildIndex;
}

void SceneManager::AddSceneToBuild(Scene* scene)
{
	mScenesInBuild.push_back(scene);
}

void SceneManager::LoadScene(std::string sceneName)
{
	// get scene by sceneName
	// LoadScene();
}

void SceneManager::LoadScene(int buildIndex)
{
	// get scene by buildIndex
	// LoadScene();
}

void SceneManager::LoadScene(Scene* scene)
{
	// clean up current scene

	// load new scene

}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}
