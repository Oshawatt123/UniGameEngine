#pragma once

#include "MathHelper.h"

class GhostControl : public Component
{
private:
	PositionComponent* pos;

	Vector2 vectorToPlayer;
	Vector2 translation;

public:

	Entity* player = nullptr;

	void Init() override
	{
		pos = &entity->getComponent<PositionComponent>();
	}

	void Tick() override
	{
		if (player != nullptr)
		{
			translation.x = 0;
			translation.y = 0;

			vectorToPlayer.x = player->getComponent<PositionComponent>().getPos().x - pos->getPos().x;
			vectorToPlayer.y = player->getComponent<PositionComponent>().getPos().y - pos->getPos().y;

			// movement towrds player
			if (vectorToPlayer.x > vectorToPlayer.y)
			{
				translation.x = vectorToPlayer.x;
			}
			else
			{
				translation.y = vectorToPlayer.y;
			}

			pos->translate(translation);
		}
	}
};