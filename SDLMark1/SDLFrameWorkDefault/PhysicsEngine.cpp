#include "PhysicsEngine.h"

bool PhysicsEngine::Tick()
{
	for (auto x : MoveAble)
	{
		x->m_position.x += x->m_velocity.x;
		x->m_position.y += x->m_velocity.y;
	}

	return true;
}

void PhysicsEngine::AddMoveableObject(GameObject* object)
{
	MoveAble.push_back(object);
}
