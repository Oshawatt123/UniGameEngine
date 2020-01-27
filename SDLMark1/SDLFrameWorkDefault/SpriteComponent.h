#pragma once
#include "PositionComponent.h"
#include "EngineStructs.h"
#include "Renderer.h"
#include "ResourceManager.h"

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
		m_bitMapPack = ResourceManager::Instance()->LoadBitMap(path, true);
	}

	void Init() override
	{
		m_positionComponent = &entity->getComponent<PositionComponent>();
		m_index = 0;
	}

	void Tick() override
	{
		Renderer::Instance()->Draw(m_bitMapPack, m_positionComponent->getPos().x, m_positionComponent->getPos().y);
	}

};