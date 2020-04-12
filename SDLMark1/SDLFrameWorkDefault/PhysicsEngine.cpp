#include "PhysicsEngine.h"

PhysicsEngine* PhysicsEngine::sInstance = NULL;

PhysicsEngine* PhysicsEngine::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new PhysicsEngine();
	}
	return sInstance;
}

bool PhysicsEngine::Tick()
{
	/*for (auto x : MoveAble)
	{
		x->m_position.x += x->m_velocity.x;
		x->m_position.y += x->m_velocity.y;
	}*/
	// make a quad tree
	for (Entity* objectA : Collidable)
	{
		objectA->getComponent<CollisionComponent>().colliding = false;
		objectA->getComponent<CollisionComponent>().other = nullptr;
		for (Entity* objectB : Collidable)
		{
			if (objectA->ID != objectB->ID)
			{
				bool collision = AABB(objectA->getComponent<CollisionComponent>().collider, objectB->getComponent<CollisionComponent>().collider);
				if (collision)
				{
					objectA->getComponent<CollisionComponent>().colliding = true;
					objectA->getComponent<CollisionComponent>().other = objectB;

					objectB->getComponent<CollisionComponent>().colliding = true;
					objectB->getComponent<CollisionComponent>().other = objectA;

					std::cout << objectA->name << " : " << objectB->name << std::endl;
				}
			}
		}
	}
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

Entity* PhysicsEngine::CheckPointCollision(Vector2 point)
{
	SDL_Rect otherCollider;

	Vector2 worldSpacePoint;
	worldSpacePoint.x = point.x * filthyRenderer->getScale() - filthyRenderer->getRenderOffset().x;
	worldSpacePoint.y = point.y * filthyRenderer->getScale() - filthyRenderer->getRenderOffset().y;
	for (auto object : Collidable)
	{
		otherCollider = object->getComponent<CollisionComponent>().collider;

		filthyRenderer->DrawLine(point.x, point.y, otherCollider.x, otherCollider.y, {0, 255, 0});
		filthyRenderer->DrawLine(point.x, point.y, otherCollider.x + otherCollider.w, otherCollider.y + otherCollider.h, {0, 255, 0});
		// Is Point X to the RIGHT of the object's LEFT edge?
		if (point.x > otherCollider.x)
		{
			// Is Point X to the LEFT of the object's RIGHT edge?
			if (point.x < (otherCollider.x + otherCollider.w))
			{
				// Is Point Y BELOW the object's TOP edge?
				if (point.y > otherCollider.y)
				{
					// Is Point Y ABOVE the object's BOTTOM edge?
					//std::string temp = std::to_string(point.y) + " < " + std::to_string(otherCollider.y + otherCollider.h);
					//Log(temp, DEBUG);
					if (point.y < (otherCollider.y + otherCollider.h))
					{
						return object;
					}
				}
			}
		}
	}
	return nullptr;
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

void PhysicsEngine::FlushEntities()
{
	MoveAble.clear();
	Collidable.clear();
}
