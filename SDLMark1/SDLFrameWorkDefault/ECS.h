#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <string>

#include "imgui.h"

class Entity;
class Component;

using ComponentID = std::size_t;

inline ComponentID getComponentTypeID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

// some useful "macros"
constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	std::string name = "Look at this descriptive name!";

	Entity* entity;

	virtual void Init() = 0;
	virtual void Tick() {};
	virtual void EditorTick() {};

	virtual ~Component() {}
};

class Entity
{
public:

	std::string name = "What a creative name!";

	std::string tag = "";

	bool editMode;

	// intended for end-user to be able to enable/disable objects
	bool enabled = true;

	// tick DOES NOT render
	void Tick()
	{
		for (auto& c : components)
		{
			if (c->name != "SpriteComponent")
			{
				c->Tick();
			}
		}
	}

	void EditorTick()
	{
		for (auto& c : components)
		{
			c->EditorTick();
		}
	}

	bool isActive() const { return active; }
	bool isEnabled() const { return enabled; }
	const std::vector<std::shared_ptr<Component>> getComponents() { return components; }

	void destroy() { active = false; }

	// check the componentBitSet to see if an object has component of type T
	template<typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	// add a component of type T to a GameObject
	template<typename T, typename... TArgs>
	T& addComponent(TArgs&& ... mArgs)
	{
		// TArgs&& is an Rvalue reference, a 'temporary' that is permitted to be modified after initialized for the purpose of 'move semantics'
		// https://en.wikipedia.org/wiki/C%2B%2B11#Rvalue_references_and_move_constructors
		// read that for a memory refresher ^^

		// create a new component of type T
		// std::forward allows the use of Rvalues in place of any other reference
		// this means we can create new components with generic arguments
		T* c(new T(std::forward<TArgs>(mArgs)...));
		// set component's entity to this
		c->entity = this;

		// create a smart pointer of our new component, and add it to the end (emplace_back) of our components vector
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		// upate array and bitset to reflect our new component
		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		// call init on the new component
		c->Init();
		return *c;
	}

	// get a component of type T
	template<typename T> T& getComponent() const
	{
		// auto is a generic chunk of data with no type
		// this allows us to grab any of our components without losing their typing
		auto ptr(componentArray[getComponentTypeID<T>()]);
		// static_cast will cast the ptr to type T, allowing us to still access all the juicy data
		return *static_cast<T*>(ptr);
	}

private:
	

	// intended for the engine to be able to track which objects to delete from memory
	bool active = true;

	std::vector<std::shared_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
};