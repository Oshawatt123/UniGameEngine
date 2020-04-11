#pragma once
#include "ECS.h"
#include "CollisionComponent.h"
#include "EventSystem.h"

class StairControl : public Component
{
private:
	CollisionComponent* col;

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
				EventSystem::Instance()->RaiseEvent(SCENE_LOAD, "Level2");
			}
		}
	}

	std::string GetSaveData()
	{
		return "";
	}
};