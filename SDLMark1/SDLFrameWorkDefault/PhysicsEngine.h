#pragma once

#include <vector>
#include "MathHelper.h"
#include "ECS.h";

class PhysicsEngine
{
private:

	std::vector<Entity*> MoveAble;
	std::vector<Entity*> Collidable;

public:
	bool Tick();

	void AddMoveableObject(Entity* object);

	void AddCollidableObject(Entity* object);

	bool CheckPointCollision(Vector2 point);
};