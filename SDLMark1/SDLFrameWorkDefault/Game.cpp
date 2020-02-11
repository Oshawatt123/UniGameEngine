#include "Game.h"

#include "Components.h"
SDL_GLContext gl_context;

Game::Game()
{
	m_Window = nullptr;

	//start up
	SDL_Init(SDL_INIT_EVERYTHING);

	//create the window
	SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE);
	m_Window = SDL_CreateWindow(
		"My First Window",	// Title
		250,				// initial x position
		50,					// initial y position
		SCREEN_WIDTH,		// width, in pixels
		SCREEN_HEIGHT,		// height, in pixels
		window_flags					// window behaviour flags
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

	ImGui::CreateContext();
	ImGuiSDL::Initialize(Renderer::Instance()->getRenderer(), 800, 600);
}

Game::~Game()
{
	// CLEAN IN REVERSE ORDER!!

	if (m_Window)
	{
		ImGuiSDL::Deinitialize();
		ImGui::DestroyContext();

		SDL_GL_DeleteContext(gl_context);

		SDL_DestroyWindow(m_Window);
	}

	SDL_Quit();

}
bool checkmate;
bool Game::Tick(void)
{

	UpdateInputManager();
	// set up ImGui input
	ImGuiIO& io = ImGui::GetIO();
	io.DeltaTime = 1.0f / 60.0f;
	float mousex, mousey;
	mousex = static_cast<float>(InputManager::Instance()->mouseX);
	mousey = static_cast<float>(InputManager::Instance()->mouseY);
	io.MousePos = ImVec2(mousex, mousey);
	io.MouseDown[0] = InputManager::Instance()->mouseButtons & SDL_BUTTON(SDL_BUTTON_LEFT);
	io.MouseDown[1] = InputManager::Instance()->mouseButtons & SDL_BUTTON(SDL_BUTTON_RIGHT);
	//io.MouseWheel = static_cast<float>(InputManager::Instance()->mouseWheel);


	// check for application quit
	if (InputManager::Instance()->WindowQuit())
	{
		return false;
	}

	// scene tick
	Level1->Tick();

	// update physics
	physicsEngine->Tick();

	UpdateRenderer();

	// do the thing with the camera

	return true;
}

bool show_demo_window = true;
void Game::UpdateRenderer(void)
{
	// add to the GUI render buffer
	ImGui::NewFrame();
	ImGui::ShowDemoWindow();

	// Clear Renderer buffer from last frame
	Renderer::Instance()->ClearRenderer();

	// draw the level, and all entities inside it
	Level1->Draw();

	// render GUI
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());

	// Update the renderer with the newly drawn Sprites
	Renderer::Instance()->UpdateRenderer();	

	
}

void Game::UpdateInputManager(void)
{
	InputManager::Instance()->Update();
}