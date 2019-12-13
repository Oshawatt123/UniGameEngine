#pragma once

#include <vector>

#include "GameObject.h"

class PhysicsEngine
{
private:

	std::vector<GameObject*> MoveAble;
	std::vector<GameObject*> Collidable;

public:
	bool Tick();

	void AddMoveableObject(GameObject* object);

	void AddCollidableObject(GameObject* object);

	bool CheckPointCollision(Vector2 point);
};