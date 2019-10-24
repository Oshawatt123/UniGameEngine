#include <SDL.h>
#include <algorithm>
#undef main
#include "Game.h"
#include "InputManager.h"

int main() {

	bool running = true;

	int red = 0;
	int green = 0;
	int blue = 255;

	Game* game = new Game();
	InputManager* inputManager = new InputManager;

	while (game != nullptr && running) {

		// take input
		inputManager->pollEvents();

		if (inputManager->checkHashMap(KeyDown) != NULL)
		{

		}
		else
		{
			std::cout << "Found null SDL_Event. No KeyDown input" << std::endl;
		}

		// update renderer
		game->SetDisplayColour(red, green, blue);
		game->UpdateRenderer();

		inputManager->clearEventQueue();
		SDL_Delay(16);
	}

	delete game;
	game = nullptr;

	return 0;
}