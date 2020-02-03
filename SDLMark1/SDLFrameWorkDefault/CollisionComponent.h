#pragma once
#include <string>
#include "SDL.h"
#include "ECS.h"
#include "PositionComponent.h"
#include "MathHelper.h"
#include "EngineStructs.h"

class CollisionComponent : public Component
{
public:

	Vector2 colPosition;
	Vector2 colDimension;
	SDL_Rect collider;

	PositionComponent* pos;

	void Init() override
	{
		pos = &entity->getComponent<PositionComponent>();
	}

	void Tick() override
	{
		colPosition = pos->getPos();
		colDimension.x = TILE_WIDTH * pos->scale;
		colDimension.y = TILE_WIDTH * pos->scale;
	}
};