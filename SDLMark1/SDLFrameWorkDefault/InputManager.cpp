#include "InputManager.h"

void InputManager::pollEvent()
{
	SDL_Event e;
	// make a smart pointer for e
	// because e will be deleted when this function ends
	// and a pointer will be 

	//get event map
			//for events in map
				//clear map



	while (SDL_PollEvent(&e) != 0)
	{
		SDL_Event* pe = new SDL_Event(e);
		//pe = &e;

		if (e.type == SDL_KEYDOWN)
		{
			frameEvents.insert(std::make_pair(KeyDown, pe));
		}


		//pe = nullptr;
	}
}

void InputManager::clearEventQueue()
{
	//del pointers first
	// delete pointer
	// nullptt
	// then I can clearthe map
	// no data breach
	frameEvents.clear();
}

SDL_Event* InputManager::checkHashMap(int eventInfo)
{
	if (frameEvents.find(eventInfo) == frameEvents.end())
	{
		return;
	}
	return frameEvents[eventInfo];
}