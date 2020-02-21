#pragma once
#include "PositionComponent.h"
#include "InputManager.h"

class CharacterController : public Component
{
private:
	PositionComponent* pos;
	float speed;
	Vector2 translation;

public:
	void Init() override
	{
		pos = & entity->getComponent<PositionComponent>();
		speed = 2;
		name = "Character Controller";
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
		pos->translate(translation);
	}

	float& GetSpeed()
	{
		return speed;
	}
};