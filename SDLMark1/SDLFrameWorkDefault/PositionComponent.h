#pragma once

class PositionComponent : public Component
{
private:
	Vector2 Position;

public:

	PositionComponent()
	{
		Position.x = 0;
		Position.y = 0;
	}
	PositionComponent(int x, int y)
	{
		Position.x = x;
		Position.y = y;
	}
	Vector2 getPos() { return Position; }

	void setPosition(int x, int y)
	{
		Position.x = x;
		Position.y = y;
	}

	void translate(int x, int y)
	{
		Position.x += x;
		Position.y += y;
	}

	void translate(Vector2 movement)
	{
		translate(movement.x, movement.y);
	}

	void Init() override
	{
	}

	void Tick() override
	{
	}
};