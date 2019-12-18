#include "Sprite.h"

void Sprite::Start()
{
	type = COMPONENT_SPRITE;
}

void Sprite::Update()
{
	Renderer::Instance()->Draw(sprite, objectTransform->Position.x, objectTransform->Position.y);
}
