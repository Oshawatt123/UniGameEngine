#pragma once
class ComponentBase
{
public:
	virtual void Start();
	virtual void Tick();
	virtual void FixedTick();
};