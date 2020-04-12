#pragma once
#include "ECS.h"
#include "CollisionComponent.h"
#include "EventSystem.h"
#include "imgui_stdlib.h"

class StairControl : public Component
{
private:
	CollisionComponent* col;
	std::string sceneToLoad;
	std::string sceneToLoadBuffer;

public:

	void Init() override
	{
		col = &entity->getComponent<CollisionComponent>();

		name = "StairControl";
	}

	void Tick() override
	{
		if (col->colliding)
		{
			if (col->other->name == "Player")
			{
				EventSystem::Instance()->RaiseEvent(SCENE_LOAD, sceneToLoad);
			}
		}
	}

	void PopulateInspector() override
	{
		ImGui::InputText("New scene to load : ", &sceneToLoadBuffer);
		ImGui::Text("Press Enter to select scene");
		if (InputManager::Instance()->KeyDown(SDL_SCANCODE_RETURN))
			sceneToLoad = sceneToLoadBuffer;
		std::string temp = "Current scene to load: " + sceneToLoad;
		ImGui::Text(temp.c_str());
	}

	std::string GetSaveData()
	{
		return "<sceneToLoad>" + sceneToLoad + "</sceneToLoad>";
	}

	void setScene(std::string _scene)
	{
		sceneToLoad = _scene;
	}
};