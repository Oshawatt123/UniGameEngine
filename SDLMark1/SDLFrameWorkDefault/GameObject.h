#pragma once

#include <stdint.h>

class GameObject
{

public:
	GameObject();
	~GameObject();

	void AddComponent(uint16_t component);

	void Tick();

private:
	uint16_t GameObjectComponents;
};