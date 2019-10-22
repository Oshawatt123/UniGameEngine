#pragma once
#include <SDL.h>
#include <unordered_map>
#include<iostream>

#include "EngineStructs.h"
class InputManager
{
public:
	void pollEvent();
	void clearEventQueue();

	std::unordered_map<int, SDL_Event*> frameEvents;

	SDL_Event* checkHashMap(int eventInfo);

private:
	bool m_keysPressed[SIZE_OF_KEYS_ENUM]
};