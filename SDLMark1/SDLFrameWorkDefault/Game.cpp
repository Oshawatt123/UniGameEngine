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

	// create physics engine
	physicsEngine = new PhysicsEngine();

	// create resource manager
	ResourceManager::Instance(Renderer::Instance()->getRenderer());

	// create my GameObject
	myGameObject = new GameObject();
	myGameObject->AddComponent(COMPONENT_Sprite);
	myGameObject->AddComponent(COMPONENT_CharacterControl);

	myGameObject->m_ObjectBitMapPack = ResourceManager::Instance()->Load("../SDLFrameWorkDefault/filthyfrank.bmp", true);

	//physicsEngine->AddMoveableObject(myGameObject);

	Level1 = new Scene("Level1");
	Level1->AddEntity(myGameObject);
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

	myGameObject->Tick();

	physicsEngine->Tick();

	UpdateRenderer();

	return true;
}

void Game::UpdateRenderer(void)
{
	// Clear Renderer buffer from last frame
	Renderer::Instance()->ClearRenderer();

	// Draw sprite for every Entity with sprite Component
	for (auto x : Level1->GetEntityList())
	{
		if ((x->m_GetComponentMask() & COMPONENT_Sprite) == COMPONENT_Sprite)
		{
			Renderer::Instance()->Draw(x->m_ObjectBitMapPack, x->m_position.x, x->m_position.y);
		}
	}

	// Update the renderer with the newly drawn Sprites
	Renderer::Instance()->UpdateRenderer();
}

void Game::UpdateInputManager(void)
{
	InputManager::Instance()->Update();
}