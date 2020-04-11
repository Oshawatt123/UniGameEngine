#pragma once
#include "PositionComponent.h"
#include "EngineStructs.h"
#include "Renderer.h"
#include "ResourceManager.h"

class SpriteComponent : public Component
{
private:

	std::string defaultPath = "../Assets/Sprites/ElvisPretzels.bmp";
	char pathBuffer[128];

	PositionComponent* m_positionComponent;

	BitMapPack m_bitMapPack;
	int m_index = 0;
	int spritesize;

public:

	std::string m_filePath;

	SpriteComponent()
	{
		m_bitMapPack = ResourceManager::Instance()->LoadBitMap(defaultPath, true);
		m_filePath = defaultPath;
	}
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

		name = "SpriteComponent";
	}

	void Tick() override
	{
		//std::cout << "Drawing a dude" << std::endl;
		Renderer::Instance()->Draw(m_bitMapPack, m_positionComponent->getPos().x, m_positionComponent->getPos().y, m_index);
	}

	SDL_Texture& getTexture()
	{
		return *m_bitMapPack.texture;
	}

	Vector2 getTexDim()
	{
		return Vector2(m_bitMapPack.width, m_bitMapPack.height);
	}

	void PopulateInspector() override
	{
		/*ImGui::InputText("File Path", pathBuffer, 64);
		if (ResourceManager::Instance()->testLoad(pathBuffer))
		{
			m_bitMapPack = ResourceManager::Instance()->LoadBitMap(pathBuffer, true);
		}*/
		//ImVec2 texSize = ImVec2(m_bitMapPack.width, m_bitMapPack.height);
		ImVec2 texSize = ImVec2(m_bitMapPack.width*3, m_bitMapPack.height*3);
		std::string temp = "Index: " + std::to_string(m_index);
		ImGui::Text(temp.c_str());
		ImGui::Image(m_bitMapPack.texture, texSize);
	}

	std::string GetSaveData()
	{
		std::string saveData;
		saveData += "<sprite>" + m_filePath + "</sprite>";
		return saveData;
	}

	void SetIndex(int index)
	{
		m_index = index;
	}
};