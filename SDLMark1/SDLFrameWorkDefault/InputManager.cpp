#include "InputManager.h"

void InputManager::pollEvent()
{
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		eventVector.push_back(e);
	}
}

void InputManager::clearEventQueue()
{
	eventVector.clear();
}
