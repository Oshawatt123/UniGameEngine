#pragma once

#include <vector>

#include "GameObject.h"

class PhysicsEngine
{
private:

	std::vector<GameObject*> MoveAble;

public:
	bool Tick();

	void AddMoveableObject(GameObject* object);
};