#pragma once

#include <stdint.h>
#include <vector>
#include "EngineStructs.h"
#include "FilthyComponents.h"
#include "MathHelper.h"

class GameObject
{

public:
	GameObject(bool isStatic = false);

	// needs to be virtual so children class can deconstruct
	virtual ~GameObject();

	void Tick();

	// ###### TO BE REMOVED AND REPLACED WITH ECS COMPONENTS #####
	// Position & Movement
	Vector2 m_position;
	Vector2 m_size;
	Vector2 m_velocity;

	// Sprite
	BitMapPack m_ObjectBitMapPack;

	// Physics Variables
	bool staticObject;
	// ############################################################

	struct transform
	{
		Vector2 position;
		Vector2 rotation;
		Vector2 scale;
	};

	struct sprite
	{
		BitMapPack bitMapPack;
	};

private:
	uint32_t m_ComponentMask;

	int ID;
};