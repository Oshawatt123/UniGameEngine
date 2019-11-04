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

	// also temp fix
	Vector2 m_position;

private:
	uint16_t m_GameObjectComponents;

};