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
	myGameObject->m_ObjectBitMapPack = ResourceManager::Instance()->Load("../SDLFrameWorkDefault/filthyfrank.bmp", false);

	World::Instance()->AddEntity(*myGameObject);

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
	UpdateInputManager();

	// check for application quit
	if (InputManager::Instance()->WindowQuit())
	{
		return false;
	}

	UpdateRenderer();

	return true;
}

#define DRAW_MASK (COMPONENT_Sprite)
void Game::UpdateRenderer(void)
{
	Renderer::Instance()->ClearRenderer();
	for (auto x : World::Instance()->GetEntityList())
	{
		if ((x.m_GetComponentMask() & DRAW_MASK) == DRAW_MASK)
		{
			Renderer::Instance()->Draw(x.m_ObjectBitMapPack, x.m_x, x.m_y);
		}
	}
	Renderer::Instance()->UpdateRenderer();
}

void Game::UpdateInputManager(void)
{
	InputManager::Instance()->Update();
}
