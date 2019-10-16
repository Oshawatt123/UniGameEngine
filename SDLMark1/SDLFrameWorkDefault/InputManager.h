#pragma once
#include <SDL.h>
#include <vector>
class InputManager
{
public:
	void pollEvent();
	void clearEventQueue();
	std::vector<SDL_Event> eventVector;

private:
};

