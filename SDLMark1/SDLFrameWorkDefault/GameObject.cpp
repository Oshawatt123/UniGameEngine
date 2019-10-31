#include "GameObject.h"
#include "EngineStructs.h"

GameObject::GameObject()
{
	m_GameObjectComponents = 0b0000000000000000;
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
