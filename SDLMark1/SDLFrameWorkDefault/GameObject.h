#pragma once

#include <stdint.h>
#include "EngineStructs.h"

class GameObject
{

public:
	GameObject();
	~GameObject();

	void AddComponent(uint16_t component);

	void Tick();

	uint16_t m_GetComponentMask();

	// temp fix
	BitMapPack m_ObjectBitMapPack;
	// also temp fix
	int m_x = 100;
	int m_y = 100;

private:
	uint16_t m_GameObjectComponents;

};