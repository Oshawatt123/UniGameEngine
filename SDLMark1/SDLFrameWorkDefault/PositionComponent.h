#pragma once

class PositionComponent : public Component
{

public:
	Vector2 Position;
	Vector2 Rotation;
	int scale;

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

	PositionComponent(int x, int y, int scale)
	{
		Position.x = x;
		Position.y = y;
		this->scale = scale;
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