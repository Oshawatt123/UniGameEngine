#pragma once
#include "EngineStructs.h"
class GameObject;

class ComponentBase
{
public:
	virtual void Start();
	virtual void Tick();
	virtual void FixedTick();

	int type;
	GameObject* owner;

private:
	static int typeID;
};