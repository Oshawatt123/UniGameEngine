#pragma once
#include "PositionComponent.h"
#include "EngineStructs.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "imgui_stdlib.h"

class SpriteComponent : public Component
{
private:

	std::string defaultPath = "../Assets/Sprites/ElvisPretzels.bmp";
	std::string pathBuffer;

	PositionComponent* m_positionComponent;

	BitMapPack m_bitMapPack;
	int m_index = 0;
	int spritesize;

	float offsetX, offsetY;

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
		offsetX = TILE_WIDTH / 2;
		offsetY = TILE_WIDTH / 2;

		name = "SpriteComponent";
	}

	void Tick() override
	{
		//std::cout << "Drawing a dude" << std::endl;
		JointTick();
	}

	void EditorTick() override
	{
		JointTick();
	}

	void JointTick()
	{
		Renderer::Instance()->Draw(m_bitMapPack, m_positionComponent->getPos().x - offsetX, m_positionComponent->getPos().y - offsetY, m_index, m_positionComponent->scale);
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
		ImGui::InputText("File path", &pathBuffer);
		if (ResourceManager::Instance()->testLoad(pathBuffer))
		{
			ImGui::Text("Press Enter to select path");
			if (InputManager::Instance()->KeyDown(SDL_SCANCODE_RETURN))
			{
				m_bitMapPack = ResourceManager::Instance()->LoadBitMap(pathBuffer, true);
				m_filePath = pathBuffer;
			}
				
		}
		else
		{
			ImGui::Text("Invalid sprite path");
		}

		ImVec2 texSize = ImVec2(m_bitMapPack.width/ m_positionComponent->scale *3, m_bitMapPack.height/ m_positionComponent->scale *3);
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