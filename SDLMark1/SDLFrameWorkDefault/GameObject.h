#pragma once

#include <stdint.h>
#include <vector>
#include "EngineStructs.h"
#include "ComponentBase.h"
#include "MathHelper.h"

class GameObject
{

public:
	GameObject(bool isStatic = false);

	// needs to be virtual so children class can deconstruct
	virtual ~GameObject();

	void Tick();

	template <class component> void addComponent();

	// ###### TO BE REMOVED AND REPLACED WITH ECS COMPONENTS #####
	// Position & Movement
	Vector2 m_position;
	Vector2 m_size;
	Vector2 m_velocity;

	// Sprite
	BitMapPack m_ObjectBitMapPack;
	// ############################################################

	// Physics Variables
	bool staticObject;

private:
	std::vector<ComponentBase*> m_GameObjectComponents;
};

template<class component>
inline void GameObject::addComponent()
{
	// get component from ECS

	// add component to component list
}
