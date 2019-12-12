#pragma once

#include <stdint.h>
#include "EngineStructs.h"
#include "MathHelper.h"

class GameObject
{

public:
	GameObject(bool isStatic = false);

	// needs to be virtual so children class can deconstruct
	virtual ~GameObject();

	void AddComponent(uint16_t component);

	void Tick();

	uint16_t m_GetComponentMask();

	// Position & Movement
	Vector2 m_position;
	Vector2 m_size;
	Vector2 m_velocity;

	// Sprite
	BitMapPack m_ObjectBitMapPack;

	// Physics Variables
	bool staticObject;

private:
	uint16_t m_GameObjectComponents;

};