#pragma once
#include "Components.h"
#include "EngineStructs.h"

class SpriteComponent : public Component
{
private:

	PositionComponent* m_positionComponent;

	BitMapPack m_bitMapPack;
	int m_index;

public:
	SpriteComponent() = default;
	SpriteComponent(std::string path)
	{

	}

	void Init() override
	{
		m_positionComponent = &entity->getComponent<PositionComponent>();
	}

	void Tick() override
	{

	}

};