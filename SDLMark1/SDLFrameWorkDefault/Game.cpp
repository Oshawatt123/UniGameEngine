#include "Game.h"

Game::Game()
{
	m_Window = nullptr;
	m_Renderer = nullptr;

	//start up
	SDL_Init(SDL_INIT_EVERYTHING);

	//create the window
	m_Window = SDL_CreateWindow(
		"My First Window",	// Title
		250,				// initial x position
		50,					// initial y position
		SCREEN_WIDTH,		// width, in pixels
		SCREEN_HEIGHT,		// height, in pixels
		0					// window behaviour flags
	);

	if (!m_Window) {
		std::cout << "WINDOW initialisation failed" << SDL_GetError() << std::endl;
		std::cout << "Press any key to continue. Please, press it and end my suffering" << std::endl;
		std::cin;
		return;
	}

	// create the renderer
	m_Renderer = SDL_CreateRenderer(
		m_Window,
		-1,
		SDL_RENDERER_ACCELERATED
	);

	if (!m_Renderer) {
		std::cout << "RENDERER initialisation failed" << SDL_GetError() << std::endl;
		std::cout << "Press any key to continue. Please, press it and end my AWFUL suffering" << std::endl;
		std::cin;
		return;
	}
}

Game::~Game()
{
	if (m_Renderer) {
		SDL_DestroyRenderer(m_Renderer);
	}

	if (m_Window) {
		SDL_DestroyWindow(m_Window);
	}
}

void Game::SetDisplayColour(int r, int g, int b)
{
	if (m_Renderer) {
		int result = SDL_SetRenderDrawColor(
			m_Renderer,	// our target renderer
			r,		// red
			g,			// green
			b,		// blue
			255			// alpha
		);
	}
}

void Game::UpdateRenderer(void)
{
	// wipe the display to the colour we just set
	SDL_RenderClear(m_Renderer);

	// show what we've drawn
	SDL_RenderPresent(m_Renderer);
}
