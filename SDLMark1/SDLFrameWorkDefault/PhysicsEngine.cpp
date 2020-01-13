#include "PhysicsEngine.h"

bool PhysicsEngine::Tick()
{
	/*for (auto x : MoveAble)
	{
		x->m_position.x += x->m_velocity.x;
		x->m_position.y += x->m_velocity.y;
	}*/
	return true;
}

void PhysicsEngine::AddMoveableObject(Entity* object)
{
	MoveAble.push_back(object);
}

void PhysicsEngine::AddCollidableObject(Entity* object)
{
	Collidable.push_back(object);
}

bool PhysicsEngine::CheckPointCollision(Vector2 point)
{
	/*for (auto object : Collidable)
	{
		// Is Point X to the RIGHT of the object's LEFT edge?
		if (point.x > object->m_position.x)
		{
			// Is Point X to the LEFT of the object's RIGHT edge?
			if (point.x < object->m_position.x + object->m_size.x)
			{
				// Is Point Y BELOW the object's TOP edge?
				if (point.y < object->m_position.y)
				{
					// Is Point Y ABOVE the object's BOTTOM edge?
					if (point.y > object->m_position.y - object->m_size.y)
					{
						return true;
					}
					return false;
				}
				return false;
			}
			return false;
		}
	}
	return false;*/

	return false;
}