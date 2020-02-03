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
	SDL_Rect otherCollider;
	for (auto object : Collidable)
	{
		otherCollider = object->getComponent<CollisionComponent>().collider;
		// Is Point X to the RIGHT of the object's LEFT edge?
		if (point.x > otherCollider.x)
		{
			// Is Point X to the LEFT of the object's RIGHT edge?
			if (point.x < otherCollider.x + otherCollider.w)
			{
				// Is Point Y BELOW the object's TOP edge?
				if (point.y < otherCollider.y)
				{
					// Is Point Y ABOVE the object's BOTTOM edge?
					if (point.y > otherCollider.y - otherCollider.h)
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
	return false;
}

bool PhysicsEngine::AABB(const SDL_Rect& A, const SDL_Rect& B)
{
	// nested for over each object? there must be a better way???
	if (
		A.x + A.w >= B.x &&
		B.x + B.w >= A.x &&
		A.y + A.h >= B.y &&
		B.y + B.h >= A.y
		)
	{
		return true;
	}

	return false;
}