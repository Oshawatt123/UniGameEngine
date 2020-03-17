#pragma once
#include "ECS.h"
#include "MathHelper.h"

class CameraComponent : public Component
{
public:

private:
	Entity* entityToFollow;

	Vector2 camPosition;
};