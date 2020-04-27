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

	Vector2 colPosition; /*!< Position of the collider.*/
	Vector2 colDimension; /*!< Size of the collider.*/
	SDL_Rect collider; /*!< A rect for storing this data compactly.*/

	PositionComponent* pos;

	bool colliding = false;

	/*!
		The other entity we are currently colliding with.
		\note If an entity collides with more than one object in one frame, the entity held here will be the one highest in the heirarchy.
	*/
	Entity* other = nullptr;

	SDL_Color drawColor = { 255, 0, 0, 255 };

	float offsetX, offsetY;

	void Init() override
	{
		pos = &entity->getComponent<PositionComponent>();
		colDimension.x = TILE_WIDTH * pos->scale;
		colDimension.y = TILE_WIDTH * pos->scale;
		offsetX = TILE_WIDTH / 2;
		offsetY = TILE_WIDTH / 2;

		name = "CollisionComponent";		
	}

	void Tick() override
	{
		colPosition = pos->getPos();
		collider.x = colPosition.x - offsetX;
		collider.y = colPosition.y - offsetX;
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
		if (entity->editMode)
		{
			colPosition = pos->getPos();
			collider.x = colPosition.x - offsetX;
			collider.y = colPosition.y - offsetX;
			collider.w = colDimension.x;
			collider.h = colDimension.y;

			Renderer::Instance()->DrawLine(collider.x, collider.y, collider.x + collider.w, collider.y + collider.h, { 0, 255, 0, 255 });
		}
	}

	std::string GetSaveData()
	{
		return "";
	}
};