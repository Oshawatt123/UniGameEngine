#pragma once
#include "Renderer.h"
#include "SDL.h"

class PositionComponent : public Component
{

public:
	Vector2 Position; /*!< The position of the Entity in world-space.*/
	Vector2 RenderPosition; /*!< The position to render the entity.*/
	Vector2 Rotation; /*!< The rotation of the entity.*/
	float scale; /*!< The scale of the entity.*/

	/*!< Base constructor takes no parameters. Sets position to 0, scale to 1.*/
	PositionComponent()
	{
		Position.x = 0;
		Position.y = 0;
		scale = 1;
	}

	/*!
		Override constructor. Position is set to the X and Y parameters. Scale is set to 1.

		\param[in] x	The x position of the Entity in world-space.
		\param[in] y	The y position of the Entity in world-space.
	*/
	PositionComponent(int x, int y)
	{
		Position.x = x;
		Position.y = y;
		scale = 1;
	}

	/*!
		Override constructor. Position is set to the X and Y parameters. Scale is set to the scale parameter.

		\param[in] x		The x position of the Entity in world-space.
		\param[in] y		The y position of the Entity in world-space.
		\param[in] scale	The scale of the Entity.
	*/
	PositionComponent(int x, int y, int scale)
	{
		Position.x = x;
		Position.y = y;
		this->scale = scale;
	}

	/*!
		A getter function for the Entity's position.

		\return Position of the entity in world-space.
	*/
	Vector2 getPos() { return Position; }

	/*!
		Sets the position of the entity.

		\param[in] x	The new x position of the entity.
		\param[in] y	The new y position of the entity.
	*/
	void setPosition(float x, float y)
	{
		Position.x = x;
		Position.y = y;
	}

	/*!
		Override for setPosition that takes a vector2 rather than 2 ints.

		\param pos	The new position of the entity.
	*/
	void setPosition(Vector2 pos)
	{
		setPosition(pos.x, pos.y);
	}

	/*!
		Translates the entity in world-space.

		\param[in] The value to translate the entity in the x-axis.
		\param[in] The value to translate the entity in the y-axis.
	*/
	void translate(float x, float y)
	{
		Position.x += x;
		Position.y += y;
	}

	/*!
		Override for translate. This calls the base function.

		\param[in] movement	The translation vector to move the entity by.
	*/
	void translate(Vector2 movement)
	{
		translate(movement.x, movement.y);
	}

	/*!
		Init sets the name of the component.
	*/
	void Init() override
	{
		name = "PositionComponent";
	}

	/*!
		Inspector is populated with sliders for position and scale.
	*/
	void PopulateInspector() override
	{		
		ImGui::DragScalar("X Position", ImGuiDataType_Float, &Position.x, 0.5f, &f_min, &f_max, "%f", 1.0f);
		ImGui::DragScalar("Y Position", ImGuiDataType_Float, &Position.y, 0.5f, &f_min, &f_max, "%f", 1.0f);
		ImGui::DragScalar("X Scale", ImGuiDataType_Float, &scale, 0.2f, &f_min, &f_max, "%f", 0.5f);
	}

	/*!
		Editor tick draws the drag box if the entity has been selected.
	*/
	void EditorTick() override
	{
		if (entity->editMode)
		{
			Renderer::Instance()->DrawLine(Position.x, Position.y, Position.x + 10, Position.y, SDL_Color{ 255, 0, 0, 255 });

			Renderer::Instance()->DrawLine(Position.x - editBoxOffset, Position.y - editBoxOffset, Position.x + editBoxOffset, Position.y - editBoxOffset, SDL_Color{ 180, 200, 54, 200});
			Renderer::Instance()->DrawLine(Position.x + editBoxOffset, Position.y - editBoxOffset, Position.x + editBoxOffset, Position.y + editBoxOffset, SDL_Color{ 180, 200, 54, 200 });
			Renderer::Instance()->DrawLine(Position.x + editBoxOffset, Position.y + editBoxOffset, Position.x - editBoxOffset, Position.y + editBoxOffset, SDL_Color{ 180, 200, 54, 200 });
			Renderer::Instance()->DrawLine(Position.x - editBoxOffset, Position.y + editBoxOffset, Position.x - editBoxOffset, Position.y - editBoxOffset, SDL_Color{ 180, 200, 54, 200 });
		}
	}

	/*!
		Save data is generated.
	*/
	std::string GetSaveData()
	{
		std::string saveData;
		saveData += "<xpos>" + std::to_string(Position.x) + "</xpos>" + "<ypos>" + std::to_string(Position.y) + "</ypos>" + "<scale>" + std::to_string(scale) + "</scale>";
		return saveData;
	}

	/*!
		QoL function for generating the drag box.
	*/
	Vector2 getEditBoxStart()
	{
		Vector2 editBoxStart;
		editBoxStart.x = Position.x - editBoxOffset;
		editBoxStart.y = Position.y - editBoxOffset;
		return editBoxStart;
	}

	/*!
		QoL function for generating the drag box.
	*/
	Vector2 getEditBoxEnd()
	{
		Vector2 editBoxEnd;
		editBoxEnd.x = Position.x + editBoxOffset;
		editBoxEnd.y = Position.y + editBoxOffset;
		return editBoxEnd;
	}


private:
	float editBoxOffset = 5;
};