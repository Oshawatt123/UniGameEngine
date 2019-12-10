#include "GameObject.h"
#include "EngineStructs.h"
#include "InputManager.h"

GameObject::GameObject()
{
	m_GameObjectComponents = 0b0000000000000000;
	m_position.x = 100;
	m_position.y = 100;
}

GameObject::~GameObject()
{
}

void GameObject::AddComponent(uint16_t component)
{
	m_GameObjectComponents |= component;
}

void GameObject::Tick()
{
	m_velocity.x = 0;
	m_velocity.y = 0;
	if (m_GameObjectComponents & COMPONENT_CharacterControl)
	{
		if (InputManager::Instance()->KeyDown(SDL_SCANCODE_D))
		{
			m_velocity.x += 5;
		}
		if (InputManager::Instance()->KeyDown(SDL_SCANCODE_A))
		{
			m_velocity.x -= 5;
		}
		if (InputManager::Instance()->KeyDown(SDL_SCANCODE_W))
		{
			m_velocity.y -= 5;
		}
		if (InputManager::Instance()->KeyDown(SDL_SCANCODE_S))
		{
			m_velocity.y += 5;
		}
	}
}

uint16_t GameObject::m_GetComponentMask()
{
	return m_GameObjectComponents;
}