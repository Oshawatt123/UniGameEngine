#include <SDL.h>
#undef main
#include "Game.h"

int main() {

	bool running = true;

	int red = 0;
	int green = 0;
	int blue = 0;

	Game* game = new Game();

	while (game != nullptr && running) {

		// this while loop COULD go on for a while
		// marked as legacy - update in future
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_y) {
					running = false;
				}
			}
		}

		// update renderer
		game->SetDisplayColour(red, green, blue);
		game->UpdateRenderer();

		SDL_Delay(16);
	}

	delete game;
	game = nullptr;

	return 0;
}