#pragma once

#include "ECS.h"
#include "MathHelper.h"

class PositionComponent : public Component
{
private:
	Vector2 Position;

public:
	Vector2 getPos() { return Position; }

	void setPosition(int x, int y)
	{
		Position.x = x;
		Position.y = y;
	}

	void init() override
	{
		Position.x = 0;
		Position.y = 0;
	}

	void tick() override
	{
		Position.x++;
		Position.y++;
		std::cout << Position.x << " , " << Position.y << std::endl;
	}
};