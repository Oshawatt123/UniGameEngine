#pragma once
#include "Components.h"
#include "InputManager.h"

class CharacterController : public Component
{
private:
	PositionComponent* pos;
	int speed;
	Vector2 translation;

public:
	void Init() override
	{
		pos = & entity->getComponent<PositionComponent>();
		speed = 2;
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
		pos->translate(translation);
	}
};