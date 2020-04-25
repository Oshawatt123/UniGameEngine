#pragma once
#include "PositionComponent.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"


#include "EngineStructs.h"
#include "AudioManager.h"
#include "Time.h"

class EnemyControl : public Component
{
private:
	PositionComponent* pos;
	CollisionComponent* col;
	SpriteComponent* spr;
	float speed;
	Vector2 translation;
	bool goingUp;

	float timer;

	int health = 3;
	bool alive = true;

public:
	void Init() override
	{
		pos = &entity->getComponent<PositionComponent>();
		col = &entity->getComponent<CollisionComponent>();
		spr = &entity->getComponent<SpriteComponent>();

		speed = 50;
		name = "EnemyControl";
		goingUp = true;
	}
	void Tick() override
	{

		if (alive)
		{
			// walk up and down
			if (goingUp)
			{
				translation.y = 1;
				if (col->colliding && timer <= 0)
				{
					goingUp = false;
					timer = 0.2f;
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
	}

	std::string GetSaveData()
	{
		return "";
	}

	void damage()
	{
		if (alive)
		{
			health -= 1;
			if (health <= 0)
			{
				alive = false;
				spr->SetIndex(5);
				filthyAudio->PlayAudio("../Assets/Audio/Hit_Hurt10.wav");
			}
			else
				filthyAudio->PlayAudio("../Assets/Audio/Hit_Hurt3.wav");
		}
	}
};