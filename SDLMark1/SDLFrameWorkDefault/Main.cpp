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

		inputManager->pollEvent();

		/*if (std::find(inputManager->eventVector.begin(), inputManager->eventVector.end(), SDL_WINDOWEVENT_CLOSE) != inputManager->eventVector.end())
		{
			running = false;
		}*/

		// update renderer
		game->SetDisplayColour(red, green, blue);
		game->UpdateRenderer();

		SDL_Delay(16);
	}

	delete game;
	game = nullptr;

	return 0;
}