#pragma once
#include "ComponentBase.h"
#include "MathHelper.h"
class Transform :
	public ComponentBase
{
public:
	void Start();

	Vector2 Position;
	Vector2 Rotation;
	Vector2 Scale;
};

