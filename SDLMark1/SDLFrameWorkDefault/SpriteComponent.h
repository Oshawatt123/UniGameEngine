#pragma once
#include "PositionComponent.h"
#include "EngineStructs.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "imgui_stdlib.h"

#include "Time.h"

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

	bool animated = false;
	float animationFrameTime = 5;
	float timer;

	std::string m_filePath;

public:

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
		if (animated)
		{
			if (timer <= 0)
			{
				m_index += 1;
				// hard-coded animation frame limit
				if (m_index >= 4)
				{
					m_index = 0;
				}
				timer = animationFrameTime;
			}
			timer -= filthyTime->deltaTime;
		}
	}

	void EditorTick() override
	{
		JointTick();
	}

	/*!
		Used in both Tick and EditorTick.
	*/
	void JointTick()
	{
		Renderer::Instance()->Draw(m_bitMapPack, m_positionComponent->getPos().x - offsetX, m_positionComponent->getPos().y - offsetY, m_index, m_positionComponent->scale);
	}

	/*!
		QoL function to get the texture of the sprite

		\return Reference to the texture of the sprite.
	*/
	SDL_Texture& getTexture()
	{
		return *m_bitMapPack.texture;
	}

	/*!
		QoL function to get the dimensions of the texture.

		\return Vector2 of the size of the texture.
	*/
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

		ImGui::Text("Index : ");
		ImGui::SameLine();
		ImGui::InputInt("", &m_index);

		ImGui::Checkbox("Animated : ", &animated);
		ImGui::InputFloat("Animation FrameTime", &animationFrameTime);

		ImVec2 texSize = ImVec2(m_bitMapPack.width/ m_positionComponent->scale *3, m_bitMapPack.height/ m_positionComponent->scale *3);
		ImGui::Image(m_bitMapPack.texture, texSize);
	}

	std::string GetSaveData()
	{
		std::string saveData;
		saveData += "<sprite>" + m_filePath + "</sprite>";
		return saveData;
	}

	/*!
		Used for animations

		\param[in] index	The new index of the sprite.
	*/
	void SetIndex(int index)
	{
		m_index = index;
	}

	/*!
		Mainly used in the inspector to change the file path of the sprite.
		Also used for animations. Changing the file path to load a different sprite sheet.

		\param[in] filePath	The new file path for the sprite.
	*/
	void setFilePath(std::string filePath)
	{
		m_filePath = filePath;
		m_bitMapPack = ResourceManager::Instance()->LoadBitMap(m_filePath, true);
	}

	/*!
		If animated, a sprite component will loop througha spritesheet's first 4 index's; creating an animation.

		\param[in] _animated	Bool to set the animated boolean.
	*/
	void SetAnimated(bool _animated)
	{
		animated = _animated;
	}
};