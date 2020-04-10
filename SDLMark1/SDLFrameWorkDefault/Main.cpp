#include <SDL.h>
#include <algorithm>
#undef main

#include "Game.h"
#include "InputManager.h"
#include "Profiler.h"
#include "Time.h"

int main()
{
	bool running = true;

	int red = 0;
	int green = 0;
	int blue = 255;

	// InputManager* IM = new InputManager();
	// renderer* R = new Renderer();
	// ResouceManager* RM = new ResourceManager(R);
	// PhysicsEngine* PE = new PhysicsEngine();

	Game* game = new Game();
	Profiler myGhettoProfiler;

	std::cout << "GET SCENE BUILD FROM SCENEMANAGER" << std::endl;

	while (game != nullptr && running)
	{
		//myGhettoProfiler.StartProfile();
		// run game main loop
		running = game->Tick();

		//SDL_Delay(32);
		//myGhettoProfiler.EndProfile();
	}

	delete game;
	game = nullptr;

	return 0;
}