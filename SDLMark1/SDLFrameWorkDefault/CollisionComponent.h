#pragma once
#include <string>
#include "SDL.h"
#include "ECS.h"
#include "PositionComponent.h"
#include "MathHelper.h"
#include "EngineStructs.h"
#include "Renderer.h"

class CollisionComponent : public Component
{
public:

	Vector2 colPosition;
	Vector2 colDimension;
	SDL_Rect collider;

	PositionComponent* pos;

	bool colliding = false;
	Entity* other = nullptr;

	SDL_Color drawColor = { 255, 0, 0, 255 };

	void Init() override
	{
		pos = &entity->getComponent<PositionComponent>();
		colDimension.x = TILE_WIDTH * pos->scale;
		colDimension.y = TILE_WIDTH * pos->scale;

		name = "CollisionComponent";
	}

	void Tick() override
	{
		colPosition = pos->getPos();
		collider.x = colPosition.x;
		collider.y = colPosition.y;
		collider.w = colDimension.x;
		collider.h = colDimension.y;		
	}

	void PopulateInspector()
	{
		std::string tempString = "Collision state: " + std::string(colliding ? "True" : "False");
		ImGui::Text(tempString.c_str());

		ImGui::Text("Other Object: ");
		ImGui::SameLine();
		if (other != nullptr)
		{
			ImGui::Text(other->name.c_str());
		}
		else
		{
			ImGui::Text("No reference to other collider");
		}
	}

	void EditorTick() override
	{
		Renderer::Instance()->DrawLine(collider.x, collider.y, collider.x + collider.w, collider.y + collider.h, {0, 255, 0, 255});
	}

	std::string GetSaveData()
	{
		return "";
	}
};