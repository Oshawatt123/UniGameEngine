#pragma once

#include "MathHelper.h"
#include "PositionComponent.h"

class CameraComponent : public Component
{
private:

	PositionComponent* pos;

	Entity* entityToFollow;
	Vector2 camPosition;


public:

	Vector2 camOffset;

	void Init() override
	{
		name = "CameraComponent";
		pos = &entity->getComponent<PositionComponent>();
	}

	void Tick() override
	{
		camPosition = pos->getPos();
	}
	
	Vector2 getPosition()
	{
		return camPosition;
	}

	void PopulateInspector() override
	{
		ImGui::DragScalar("Camera X Offset", ImGuiDataType_Float, &camOffset.x, 0.5f, &f_min, &f_max, "%f", 1.0f);
		ImGui::DragScalar("Camera Y Offset", ImGuiDataType_Float, &camOffset.y, 0.5f, &f_min, &f_max, "%f", 1.0f);
		if (ImGui::Button("Center Camera"))
		{
			camOffset.x = 1920 / 2;
			camOffset.y = 1080 / 2;
		}
	}
};