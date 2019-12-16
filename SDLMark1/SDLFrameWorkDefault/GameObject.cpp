#include "GameObject.h"
#include "EngineStructs.h"
#include "InputManager.h"

GameObject::GameObject(bool isStatic)
{
	m_position.x = 0;
	m_position.y = 0;

	m_size.x = TILE_WIDTH;
	m_size.y = TILE_WIDTH;

	staticObject = isStatic;
}

GameObject::~GameObject()
{

}

void GameObject::Tick()
{
	// Reset velocity
	m_velocity.x = 0;
	m_velocity.y = 0;

	/*if (m_GameObjectComponents & COMPONENT_CharacterControl)
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
	}*/
}