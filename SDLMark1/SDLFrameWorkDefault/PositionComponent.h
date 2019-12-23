#pragma once
#include "Components.h"

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

	void Init() override
	{
		Position.x = 0;
		Position.y = 0;
	}

	void Tick() override
	{
		Position.x++;
		Position.y++;
		std::cout << Position.x << " , " << Position.y << std::endl;
	}
};