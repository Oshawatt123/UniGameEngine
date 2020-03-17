#pragma once

#include "MathHelper.h"
#include "PositionComponent.h"

class CameraComponent : public Component
{
public:

	void Init() override
	{
		name = "CameraComponent";
		pos = &entity->getComponent<PositionComponent>();
	}

	void Tick() override
	{
		camPosition = pos->getPos();
	}
	
	Vector2 getPosition()
	{
		return camPosition;
	}

	Vector2 camOffset;

private:

	PositionComponent* pos;

	Entity* entityToFollow;
	Vector2 camPosition;
};