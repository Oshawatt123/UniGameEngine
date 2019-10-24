#include "Game.h"
#include "Bitmap.h"
#include "ResourceManager.h"
#include "InputManager.h"

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

	// create resource manager
	ResourceManager* resourceManager = new ResourceManager(m_Renderer);

	// create the bitmap
	for (size_t i = 0; i < 100; i++)
	{
		m_wood = new Bitmap(m_Renderer, 200, 100, resourceManager->Load("filthyFrank.bmp", true));
	}
}

Game::~Game()
{
	// CLEAN IN REVERSE ORDER!!
	delete m_wood;

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

	m_wood->draw();

	// show what we've drawn
	SDL_RenderPresent(m_Renderer);
}
