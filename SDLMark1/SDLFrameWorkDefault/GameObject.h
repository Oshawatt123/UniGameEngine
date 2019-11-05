#pragma once

#include <stdint.h>
#include "EngineStructs.h"
#include "MathHelper.h"

class GameObject
{

public:
	GameObject();

	// needs to be virtual so children class can deconstruct
	virtual ~GameObject();

	void AddComponent(uint16_t component);

	void Tick();

	uint16_t m_GetComponentMask();

	// Position & Movement
	Vector2 m_position;
	Vector2 m_velocity;

	// Sprite
	BitMapPack m_ObjectBitMapPack;

private:
	uint16_t m_GameObjectComponents;

};