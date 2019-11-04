#include "GameObject.h"
#include "EngineStructs.h"

GameObject::GameObject()
{
	m_GameObjectComponents = 0b0000000000000000;

	m_ObjectBitMapPack.texture = NULL;
	m_ObjectBitMapPack.width = 0;
	m_ObjectBitMapPack.height = 0;
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

}

uint16_t GameObject::m_GetComponentMask()
{
	return m_GameObjectComponents;
}
