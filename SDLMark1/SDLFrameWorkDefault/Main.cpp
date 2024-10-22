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

	while (game != nullptr && running)
	{
		// update input

		// update renderer
		game->SetDisplayColour(red, green, blue);
		game->UpdateRenderer();

		SDL_Delay(16);
	}

	delete game;
	game = nullptr;

	return 0;
}