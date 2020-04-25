#pragma once
#include "PositionComponent.h"
#include "CollisionComponent.h"
#include "SpriteComponent.h"
#include "EnemyControl.h"

#include "InputManager.h"
#include "EngineStructs.h"
#include "MathHelper.h"
#include "Time.h"

#include "PhysicsEngine.h"

class CharacterController : public Component
{
private:
	PositionComponent* pos;
	CollisionComponent* col;
	SpriteComponent* spr;

	float speed;
	Vector2 translation;
	Vector2 direction;
	Entity* collidingEntity;

	float timeBetweenAttacks = 1.0f;
	float attackTimer;

public:
	void Init() override
	{
		pos = &entity->getComponent<PositionComponent>();
		col = &entity->getComponent<CollisionComponent>();
		spr = &entity->getComponent<SpriteComponent>();

		speed = 100;
		name = "CharacterController";
	}
	void Tick() override
	{
		translation.x = 0;
		translation.y = 0;
		if (InputManager::Instance()->KeyDown(SDL_SCANCODE_D))
		{
			translation.x += speed;
			spr->SetIndex(2);
		}
		if (InputManager::Instance()->KeyDown(SDL_SCANCODE_A))
		{
			translation.x -= speed;
			spr->SetIndex(1);
		}
		if (InputManager::Instance()->KeyDown(SDL_SCANCODE_W))
		{
			translation.y -= speed;
			spr->SetIndex(3);
		}
		if (InputManager::Instance()->KeyDown(SDL_SCANCODE_S))
		{
			translation.y += speed;
			spr->SetIndex(0);
		}
		if (InputManager::Instance()->KeyDown(SDL_SCANCODE_Q))
		{
			translation *= 2;
			std::cout << "DASSHHHHH" << std::endl;
			std::cout << "DASSHHHHH" << std::endl;
			std::cout << "DASSHHHHH" << std::endl;
			std::cout << "DASSHHHHH" << std::endl;
			std::cout << "DASSHHHHH" << std::endl;
			std::cout << "DASSHHHHH" << std::endl;
			std::cout << "DASSHHHHH" << std::endl;

		}

		if (translation.x != 0 || translation.y != 0)
		{
			direction = translation;
			direction.Normalize();
			direction *= TILE_WIDTH + 2;
		}

		collidingEntity = Physics->CheckPointCollision(pos->getPos().Add(direction));
		if (collidingEntity)
		{
			if (collidingEntity->name == "Block")
				translation = Vector2(0, 0);
		}
		pos->translate(translation * filthyTime->deltaTime);

		if (InputManager::Instance()->KeyDown(SDL_SCANCODE_SPACE) && attackTimer <= 0)
		{
			attackTimer = timeBetweenAttacks;
			if (collidingEntity)
			{
				if (collidingEntity->name == "Crab")
				{
					collidingEntity->getComponent<EnemyControl>().damage();
				}
			}
		}

		// set sprite and animation
		if (translation.Magnitude() > 0)
		{
			spr->setFilePath("../Assets/Sprites/knight.bmp");
			spr->SetAnimated(false);
		}
		else
		{
			spr->setFilePath("../Assets/Sprites/knightIdle.bmp");
			spr->SetAnimated(true);
		}

		attackTimer -= filthyTime->deltaTime;

		filthyRenderer->DrawLine(pos->getPos().x, pos->getPos().y, pos->getPos().x + direction.x, pos->getPos().y + direction.y);
	}

	void PopulateInspector() override
	{
		std::string temp = "Direction => X: " + std::to_string(direction.x) + " Y: " + std::to_string(direction.y);
		ImGui::Text(temp.c_str());
		if (collidingEntity)
			temp = "About to collide with: " + collidingEntity->name;
		else
			temp = "No collision inbound";
		ImGui::Text(temp.c_str());

		temp = std::to_string(translation.Magnitude());
		ImGui::Text(temp.c_str());
	}

	float& GetSpeed()
	{
		return speed;
	}

	std::string GetSaveData()
	{
		return "";
	}
};