#pragma once

#include <vector>
#include "MathHelper.h"
#include "ECS.h"
#include "CollisionComponent.h"

class PhysicsEngine
{
private:

	std::vector<Entity*> MoveAble;
	std::vector<Entity*> Collidable;

	static PhysicsEngine* sInstance;

public:

	static PhysicsEngine* Instance();

	bool Tick();

	void AddMoveableObject(Entity* object);

	void AddCollidableObject(Entity* object);

	bool CheckPointCollision(Vector2 point, Entity* outEntity);

	bool AABB(const SDL_Rect& A, const SDL_Rect& B);

private:
	PhysicsEngine() {}
	~PhysicsEngine() {}
};