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

	bool colliding;

	void Init() override
	{
		pos = &entity->getComponent<PositionComponent>();
		colDimension.x = TILE_WIDTH * pos->scale;
		colDimension.y = TILE_WIDTH * pos->scale;
	}

	void Tick() override
	{
		colPosition = pos->getPos();
		collider.x = colPosition.x;
		collider.y = colPosition.y;
		collider.w = colDimension.x;
		collider.h = colDimension.y;

#ifdef RENDER_DEBUG
		Renderer::Instance()->DrawLine(collider.x, collider.y, collider.x+collider.w, collider.y+collider.h);
#endif
	}
};