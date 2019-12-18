#pragma once
#include "ComponentBase.h"
#include "Transform.h"
#include "Sprite.h"
#include "GameObject.h"
#include <unordered_map>

template <class component>
std::unordered_map<ComponentType, component> staticComponentList;

void ECSGetComponent(ComponentType componentType)
{
	
}

class ECS
{

};