#pragma once

#include "Logger.h"

class Component;
class Entity;

class Component
{
public:
	Entity* entity;
};

class ECS
{
public:
	bool active = true;
};