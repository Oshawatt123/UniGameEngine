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

	// set up render viewport
	renderCamera.x = SCREEN_WIDTH * 0.25;
	renderCamera.y = SCREEN_HEIGHT * 0.05;
	renderCamera.w = RENDER_VIEW_WIDTH;
	renderCamera.h = RENDER_VIEW_HEIGHT;

	// create renderer
	Renderer::Instance(m_Window, &camera, &renderCamera);

	// create physics engine
	physicsEngine = new PhysicsEngine();

	// create resource manager
	ResourceManager::Instance(Renderer::Instance()->getRenderer());

	// replace this with a build list of scenes and load the first one in
	Level1 = new Scene("Level1", physicsEngine, &camera, RENDER_VIEW_WIDTH, RENDER_VIEW_HEIGHT);
}

Game::~Game()
{
	// CLEAN IN REVERSE ORDER!!

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

	// update physics
	physicsEngine->Tick();

	UpdateRenderer();

	// do the thing with the camera

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