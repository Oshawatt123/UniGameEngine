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
	mNextBuildIndex += 1;
}

void SceneManager::LoadScene(std::string sceneName)
{
	// get scene by name
	// if scene does not exist already
	std::string path = "../Assets/Scenes/" + sceneName + ".filthyscene";
	if ((loadedScenes.find(path) == loadedScenes.end()))
	{
		Scene* newScene = new Scene(sceneName, 1920, 1080);
		loadedScenes.insert(std::pair<std::string, Scene*>(path, newScene));
	}
	LoadScene(loadedScenes[path]);
}

void SceneManager::LoadScene(int buildIndex)
{
	// get scene by buildIndex
	// LoadScene();
}

void SceneManager::LoadSceneByPath(std::string path)
{
	// get scene by path
	// if scene does not exist already

	// cut the string until we get the name
	// cut the front off : "../assets/scenes/" - 17
	std::string levelName = "";
	levelName = path.substr(17, path.length() - 17);
	std::cout << levelName << std::endl;

	// cut the end off ".filthyscene" - 12
	levelName = levelName.substr(0, levelName.length() - 12);
	std::cout << levelName << std::endl;

	// voila!!!
	if ((loadedScenes.find(path) == loadedScenes.end()))
	{
		Scene* newScene = new Scene(levelName, 1920, 1080);
		loadedScenes.insert(std::pair<std::string, Scene*>(path, newScene));
	}
	LoadScene(loadedScenes[path]);
}

void SceneManager::LoadSceneByPathNoSave(std::string path)
{
	// get scene by path
	// if scene does not exist already

	// cut the string until we get the name
	// cut the front off : "../assets/scenes/" - 17
	std::string levelName = "";
	levelName = path.substr(17, path.length() - 17);
	std::cout << levelName << std::endl;

	// cut the end off ".filthyscene" - 12
	levelName = levelName.substr(0, levelName.length() - 12);
	std::cout << levelName << std::endl;

	LoadSceneNoSave(levelName);
}

void SceneManager::LoadSceneNoSave(std::string sceneName)
{
	// get scene by name

	// if scene does not exist already
	std::string path = "../Assets/Scenes/" + sceneName + ".filthyscene";
	if ((loadedScenes.find(path) == loadedScenes.end()))
	{
		Scene* newScene = new Scene(sceneName, 1920, 1080);
		loadedScenes.insert(std::pair<std::string, Scene*>(path, newScene));
	}

	currentScene = loadedScenes[path];
	currentScene->Reload();
}

void SceneManager::SaveScene()
{
	std::ofstream outfile;
	std::string scenePath = "../Assets/Scenes/" + currentScene->GetName() + ".filthyscene";
	outfile.open(scenePath);
	// do the save
	outfile << currentScene->generateSaveData();

	outfile.close();

	currentScene->Reload();
}

Scene* SceneManager::getCurrentScene()
{
	return currentScene;
}

void SceneManager::Tick()
{
	eventStore = EventSystem::Instance()->GetEvent(SCENE_LOAD);
	if (eventStore)
	{
		LoadSceneNoSave(eventStore->stringData);
		eventStore = nullptr;
	}
}

void SceneManager::LoadScene(Scene* scene)
{
	// clean up current scene
	if (currentScene)
	{
		std::ofstream outfile;
		std::string scenePath = "../Assets/Scenes/" + currentScene->GetName() + ".filthyscene";
		outfile.open(scenePath);
		// do the save
		outfile << currentScene->generateSaveData();

		outfile.close();

	}
	// load new scene
	currentScene = scene;
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}