#pragma once
#include "Renderer.h"
#include "SDL.h"

class PositionComponent : public Component
{

public:
	Vector2 Position;
	Vector2 RenderPosition;
	Vector2 Rotation;
	int scale;

	PositionComponent()
	{
		Position.x = 0;
		Position.y = 0;
		scale = 1;
	}
	PositionComponent(int x, int y)
	{
		Position.x = x;
		Position.y = y;
		scale = 1;
	}

	PositionComponent(int x, int y, int scale)
	{
		Position.x = x;
		Position.y = y;
		this->scale = scale;
	}

	Vector2 getPos() { return Position; }

	void setPosition(float x, float y)
	{
		Position.x = x;
		Position.y = y;
	}

	void setPosition(Vector2 pos)
	{
		setPosition(pos.x, pos.y);
	}

	void translate(float x, float y)
	{
		Position.x += x;
		Position.y += y;
	}

	void translate(Vector2 movement)
	{
		translate(movement.x, movement.y);
	}

	void Init() override
	{
		name = "PositionComponent";
	}

	void PopulateInspector() override
	{		
		ImGui::DragScalar("X Position", ImGuiDataType_Float, &Position.x, 0.5f, &f_min, &f_max, "%f", 1.0f);
		ImGui::DragScalar("Y Position", ImGuiDataType_Float, &Position.y, 0.5f, &f_min, &f_max, "%f", 1.0f);
	}

	void EditorTick() override
	{
		if (entity->editMode)
		{
			Renderer::Instance()->DrawLine(Position.x, Position.y, Position.x + 10, Position.y, SDL_Color{ 255, 0, 0, 255 });
		}
	}

	std::string GetSaveData()
	{
		std::string saveData;
		saveData += "<xpos>" + std::to_string(Position.x) + "</xpos>" + "<ypos>" + std::to_string(Position.y) + "</ypos>" + "<scale>" + std::to_string(scale) + "</scale>";
		return saveData;
	}
};