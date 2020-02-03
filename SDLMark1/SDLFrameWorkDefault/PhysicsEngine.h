#pragma once

#include <vector>
#include "MathHelper.h"
#include "ECS.h"
#include "Components.h"

class PhysicsEngine
{
private:

	std::vector<Entity*> MoveAble;
	std::vector<Entity*> Collidable;

public:

	PhysicsEngine() {}
	~PhysicsEngine() {}
	bool Tick();

	void AddMoveableObject(Entity* object);

	void AddCollidableObject(Entity* object);

	bool CheckPointCollision(Vector2 point);

	bool AABB(const SDL_Rect& A, const SDL_Rect& B);
};