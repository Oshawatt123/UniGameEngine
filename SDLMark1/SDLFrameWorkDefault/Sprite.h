#pragma once
#include "ComponentBase.h"
#include "EngineStructs.h"
#include "Renderer.h"
#include "Transform.h"

class Sprite :
	public ComponentBase
{
public:
	void Start();
	void Update();

	Transform* objectTransform;
	SDL_Rect* destRect;
	BitMapPack sprite;
};

