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

	std::string m_filePath;

	SpriteComponent() = default;
	SpriteComponent(std::string path)
	{
		m_bitMapPack = ResourceManager::Instance()->LoadBitMap(path, true);
		m_filePath = path;
	}

	// Init is not called in the constructor because if we add components, they are created and if we add them in a weird order, it will still work as long as we
	// have a position component on the object since Init() happens after a full load
	void Init() override
	{
		m_positionComponent = &entity->getComponent<PositionComponent>();
		m_index = 0;
		m_bitMapPack.width *= entity->getComponent<PositionComponent>().scale;
		m_bitMapPack.height *= entity->getComponent<PositionComponent>().scale;

		name = "Sprite Component";
	}

	void Tick() override
	{
		//std::cout << "Drawing a dude" << std::endl;
		Renderer::Instance()->Draw(m_bitMapPack, m_positionComponent->getPos().x, m_positionComponent->getPos().y);
	}

	SDL_Texture& getTexture()
	{
		return *m_bitMapPack.texture;
	}

	Vector2 getTexDim()
	{
		return Vector2(m_bitMapPack.width, m_bitMapPack.height);
	}

};