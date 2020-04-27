#pragma once

#include "MathHelper.h"
#include "PositionComponent.h"

class CameraComponent : public Component
{
private:

	PositionComponent* pos; /*!< Reference to the PositionComponent.*/

	Entity* entityToFollow; /*!< Reference to the entity to follow.*/
	Vector2 camPosition; /*!< The position of the camera, for use in generating offset.*/


public:

	Vector2 camOffset; /*!< The offset of the camera which is used in rendering the scene relative to the camera.*/

	void Init() override
	{
		name = "CameraComponent";
		pos = &entity->getComponent<PositionComponent>();
	}

	void Tick() override
	{
		camPosition.x = pos->getPos().x * Renderer::Instance()->getScale();
		camPosition.y = pos->getPos().y * Renderer::Instance()->getScale();
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

	std::string GetSaveData()
	{
		std::string saveData;
		saveData += "<xpos>" + std::to_string(camOffset.x) + "</xpos>" + "<ypos>" + std::to_string(camOffset.y) + "</ypos>";
		return saveData;
	}

	void setCamPosition(int _x, int _y)
	{
		camOffset.x = _x;
		camOffset.y = _y;
	}
};