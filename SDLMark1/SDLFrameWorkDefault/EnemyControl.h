#pragma once
#include "PositionComponent.h"
#include "InputManager.h"
#include "EngineStructs.h"
#include "Time.h"

class EnemyControl : public Component
{
private:
	PositionComponent* pos;
	CollisionComponent* col;
	float speed;
	Vector2 translation;
	bool goingUp;

	float timer;

public:
	void Init() override
	{
		pos = &entity->getComponent<PositionComponent>();
		col = &entity->getComponent<CollisionComponent>();
		speed = 50;
		name = "EnemyControl";
		goingUp = true;
	}
	void Tick() override
	{
		// walk up and down
		if (goingUp)
		{
			translation.y = 1;
			if (col->colliding && timer <= 0)
			{
				goingUp = false;
				timer = 1;
			}
		}
		else
		{
			translation.y = -1;
			if (col->colliding && timer <= 0)
			{
				goingUp = true;
				timer = 1;
			}
		}

		pos->translate(translation * speed * filthyTime->deltaTime);
		timer -= filthyTime->deltaTime;
	}

	std::string GetSaveData()
	{
		return "";
	}
};