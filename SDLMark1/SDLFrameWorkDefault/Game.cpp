#include "Game.h"

#include "Components.h"

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

	// create physics engine
	physicsEngine = new PhysicsEngine();

	// create resource manager
	ResourceManager::Instance(Renderer::Instance()->getRenderer());

	// create my Entity
	Entity* player = new Entity();
	player->addComponent<PositionComponent>();
	player->addComponent<SpriteComponent>("../Sprites/ElvisPretzels.bmp");

	Level1 = new Scene("Level1");
	Level1->AddEntity(player);

	// Make the physics thread
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

void Game::UpdateRenderer(void)
{
	// Clear Renderer buffer from last frame
	Renderer::Instance()->ClearRenderer();

	// THIS DOES MORE THAN DRAW AT THE MOMENT
	// SPLIT THIS INTO TICK AND DRAW
	Level1->Draw();

	// Update the renderer with the newly drawn Sprites
	Renderer::Instance()->UpdateRenderer();
}

void Game::UpdateInputManager(void)
{
	InputManager::Instance()->Update();
}