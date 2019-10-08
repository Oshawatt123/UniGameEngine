#include <SDL.h>
#undef main
#include "Game.h"

int main() {

	Game* game = new Game();

	if (game) {
		game->SetDisplayColour();
		delete game;
		game = nullptr;
	}

	return 0;
}