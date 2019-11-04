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

private:
	uint16_t m_GameObjectComponents;
	
	int x, y = 100;

	BitMapPack m_ObjectBitMapPack;
};