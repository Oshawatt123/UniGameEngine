#pragma once

#include <vector>
#include "MathHelper.h"
#include "ECS.h"
#include "CollisionComponent.h"

/*!
	The Physics Engine is not a fully fledged physics engine.
	This does NOT handle collisions. It will only detect and report collisions to the objects that have collided.
*/
class PhysicsEngine
{
private:

	/*! 
		All move-able objects in the scene.
		\note NOT implemented. Originally intended to be used as a method of the physics system moving objects and handling collisions itself. This is now the responsibility of the individual entity.
	*/
	std::vector<Entity*> MoveAble;

	std::vector<Entity*> Collidable; /*!< All collidable entities.*/

	static PhysicsEngine* sInstance;/*!< Static instance of the PhysicsEngine class. */

public:

	/*!
		Method for getting an instance of PhysicsEngine.
	*/
	static PhysicsEngine* Instance(); 

	/*!
		Ticks the physics engine.

		All collision checks happen in this function.

		It uses a nested-for loop over all objects in the scene.

		\note A quad tree is planned for the second version.
	*/
	bool Tick();

	/*!
		Adds an object to the MoveAble vector.

		\param[in] object	The entity to add into the MoveAble vector.
	*/
	void AddMoveableObject(Entity* object);

	/*!
		Adds an object to the Collidable vector.

		/param[in] object	The entity to add into the collidable vector.
	*/
	void AddCollidableObject(Entity* object);

	/*!
		Checks if a point collides with anything in the collidables vector.

		\param[in] point	The point to check collisions for.

		\return A reference to the entity collided with. nullptr if nothing is collided.
	*/
	Entity* CheckPointCollision(Vector2 point);

	/*!
		Performs an AABB collision test for overlapping rectangles.

		\param[in] A	The first rectangle to check collisions with.
		\param[in] B	The second rectangle to check collisions with.

		\return Whether there was an overlap on the two rectangles.
	*/
	bool AABB(const SDL_Rect& A, const SDL_Rect& B);

	/*!
		Flushes all entities out of the system.

		This is required every time we load a new scene as the old scene objects are still in the system and will register collisions.
	*/
	void FlushEntities();

private:
	PhysicsEngine() {}
	~PhysicsEngine() {}
};