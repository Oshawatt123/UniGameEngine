#include "Game.h"

#include "ECS.h"

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
	//myGameObject->AddComponent(COMPONENT_Sprite);
	//myGameObject->AddComponent(COMPONENT_CharacterControl);

	myGameObject->m_ObjectBitMapPack = ResourceManager::Instance()->LoadBitMap("../Sprites/Mudkip.bmp", true);

	myCollidableObject = new GameObject();
	//myCollidableObject->AddComponent(COMPONENT_Collidable);
	//myCollidableObject->AddComponent(COMPONENT_Sprite);

	myCollidableObject->m_ObjectBitMapPack = ResourceManager::Instance()->LoadBitMap("../Sprites/Floor_Placeholder.bmp", true);

	physicsEngine->AddMoveableObject(myGameObject);
	physicsEngine->AddCollidableObject(myCollidableObject);

	Level1 = new Scene("Level1");
	Level1->AddEntity(myGameObject);
	Level1->AddEntity(myCollidableObject);

	// Make the physics thread

	// Component testing
	std::cout << getComponentTypeID<ComponentBase>();
	std::cout << getComponentTypeID<Transform>();
	std::cout << getComponentTypeID<Sprite>();
	std::cout << getComponentTypeID<Transform>();
	std::cout << getComponentTypeID<Transform>();
	std::cout << getComponentTypeID<Transform>();
	std::cout << getComponentTypeID<Sprite>();
	std::cout << getComponentTypeID<Sprite>();
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
	myCollidableObject->Tick();

	physicsEngine->Tick();

	std::cout << physicsEngine->CheckPointCollision(myGameObject->m_position) << std::endl;

	UpdateRenderer();

	return true;
}

void Game::UpdateRenderer(void)
{
	// Clear Renderer buffer from last frame
	Renderer::Instance()->ClearRenderer();

	Level1->Draw();

	// Update the renderer with the newly drawn Sprites
	Renderer::Instance()->UpdateRenderer();
}

void Game::UpdateInputManager(void)
{
	InputManager::Instance()->Update();
}