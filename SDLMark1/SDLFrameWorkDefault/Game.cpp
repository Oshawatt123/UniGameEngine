#include "Game.h"


Game::Game()
{
	m_Window = nullptr;

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

	if (!m_Window)
	{
		std::cout << "WINDOW initialisation failed" << SDL_GetError() << std::endl;
		std::cout << "Press any key to continue. Please, press it and end my suffering" << std::endl;
		std::cin;
		return;
	}

	// create renderer
	Renderer::Instance(m_Window);

	// create resource manager
	ResourceManager::Instance(Renderer::Instance()->getRenderer());

	// create my GameObject
	myGameObject = new GameObject();
	myGameObject->AddComponent(COMPONENT_Sprite);

}

Game::~Game()
{
	// CLEAN IN REVERSE ORDER!!
	delete myGameObject;

	if (m_Window)
	{
		SDL_DestroyWindow(m_Window);
	}

	
}

bool Game::Tick(void)
{
	//UpdateRenderer();
	InputManager::Instance()->Update();

	if (InputManager::Instance()->WindowQuit())
	{
		return false;
	}


	return true;
}



void Game::UpdateRenderer(void)
{
	for (auto x : World::Instance()->GetEntityList())
	{
		// check if entity is renderable
	}
	
}

void Game::UpdateInputManager(void)
{
	InputManager::Instance()->Update();
}
