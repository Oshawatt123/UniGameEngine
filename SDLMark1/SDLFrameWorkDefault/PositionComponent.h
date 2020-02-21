#pragma once

class PositionComponent : public Component
{

public:
	Vector2 Position;
	Vector2 RenderPosition;
	Vector2 Rotation;
	int scale;

	PositionComponent()
	{
		Position.x = 0;
		Position.y = 0;
		scale = 1;
	}
	PositionComponent(int x, int y)
	{
		Position.x = x;
		Position.y = y;
		scale = 1;
	}

	PositionComponent(int x, int y, int scale)
	{
		Position.x = x;
		Position.y = y;
		this->scale = scale;
	}

	Vector2 getPos() { return Position; }
	Vector2& getPosAddr() { return Position; }

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
		name = "Position Component";
	}

	void Tick() override
	{
	}
};