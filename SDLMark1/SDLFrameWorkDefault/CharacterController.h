#pragma once
#include "PositionComponent.h"
#include "CollisionComponent.h"
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
	float speed;
	Vector2 translation;
	Vector2 direction;
	Entity* collidingEntity;

public:
	void Init() override
	{
		pos = &entity->getComponent<PositionComponent>();
		col = &entity->getComponent<CollisionComponent>();
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
		}
		if (InputManager::Instance()->KeyDown(SDL_SCANCODE_A))
		{
			translation.x -= speed;
		}
		if (InputManager::Instance()->KeyDown(SDL_SCANCODE_W))
		{
			translation.y -= speed;
		}
		if (InputManager::Instance()->KeyDown(SDL_SCANCODE_S))
		{
			translation.y += speed;
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

		Physics->CheckPointCollision(pos->getPos().Add(direction), collidingEntity);
		if (collidingEntity)
		{
			if (collidingEntity->name == "Block")
				translation = Vector2(0, 0);
		}
		pos->translate(translation * filthyTime->deltaTime);

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