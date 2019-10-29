#include "GameObject.h"
#include "EngineStructs.h"

GameObject::GameObject()
{
	GameObjectComponents = 0b0000000000000000;
}

GameObject::~GameObject()
{
}

void GameObject::AddComponent(uint16_t component)
{
	GameObjectComponents |= component;
}

void GameObject::Tick()
{

}
