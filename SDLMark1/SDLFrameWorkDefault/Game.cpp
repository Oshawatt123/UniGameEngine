#include "Game.h"


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
		0,					// initial x position
		10,					// initial y position
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

	ImGui::CreateContext();
	ImGuiSDL::Initialize(Renderer::Instance()->getRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);



	// ##### hard-coding ##### //


	// replace this with a build list of scenes and load the first one in
	Level1 = new Scene("Level1", physicsEngine, &camera, RENDER_VIEW_WIDTH, RENDER_VIEW_HEIGHT);

	currentSelectedEntity = nullptr;

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

	if (!EditMode)
	{
		// scene tick
		Level1->Tick();

		// update physics
		physicsEngine->Tick();
	}
	else
	{
		if (InputManager::Instance()->mouseButtons && SDL_BUTTON_LMASK)
		{

		}
	}

	// check for application quit
	if (InputManager::Instance()->WindowQuit())
	{
		return false;
	}

	UpdateRenderer();

	return true;
}

bool firstToolOpen = true;
bool heirarchyOpen = true;
bool inspectorOpen = true;

void Game::UpdateRenderer(void)
{
	// Add to the ImGui frame buffer
	ImGui::NewFrame();
	ImGui::ShowDemoWindow();

	ImGui::Begin("My First Tool", &firstToolOpen, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("Open");
			ImGui::MenuItem("Lmao");
			ImGui::MenuItem("Baited");
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	const float my_value[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
	ImGui::PlotLines("Frame time", my_value, IM_ARRAYSIZE(my_value));

	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Really important jazz");
	ImGui::BeginChild("Scrolling child");
	for (int n = 0; n < 50; n++)
	{
		ImGui::Text("%04d: Some text", n);
	}
	ImGui::EndChild();
	ImGui::End();

	DrawHeirarchy();

	DrawInspector();

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

void Game::DrawHeirarchy()
{
	// Heirarchy Window
	ImGui::Begin("Heirarchy", &heirarchyOpen);
	ImGui::TextColored(ImVec4(1, 0, 1, 1), Level1->GetName().c_str());

	// populate heirarchy
	if (ImGui::BeginChild("EntityList"))
	{
		ImGui::Text("");
		Level1->PopulateHeirarchy();
	}

	ImGui::EndChild();
	ImGui::End();
}

void Game::DrawInspector()
{
	ImGui::Begin("Entity Inspector", &inspectorOpen);
	if (currentSelectedEntity != nullptr)
	{
		ImGui::Checkbox("EntityEnabledCheck", &currentSelectedEntity->enabled);
		ImGui::TextColored(ImVec4(1, 1, 0, 1), currentSelectedEntity->name.c_str());

		for (auto component : currentSelectedEntity->getComponents())
		{
			ImGui::Text(component->name.c_str());
			if (component->name == "Position Component")
			{
				ImGui::Text(std::to_string(currentSelectedEntity->getComponent<PositionComponent>().getPos().x).c_str());

				ImGui::DragScalar("X Position", ImGuiDataType_Float, &currentSelectedEntity->getComponent<PositionComponent>().getPosAddr().getXAddr(), 0.5f, &f_min, &f_max, "%f", 1.0f);
				ImGui::DragScalar("Y Position", ImGuiDataType_Float, &currentSelectedEntity->getComponent<PositionComponent>().getPosAddr().getYAddr(), 0.5f, &f_min, &f_max, "%f", 1.0f);
			}
			else if (component->name == "Sprite Component")
			{
				ImGui::Text(currentSelectedEntity->getComponent<SpriteComponent>().m_filePath.c_str());

				ImVec2 texSize = ImVec2(currentSelectedEntity->getComponent<SpriteComponent>().getTexDim().x, currentSelectedEntity->getComponent<SpriteComponent>().getTexDim().y);


				ImGui::Image(&currentSelectedEntity->getComponent<SpriteComponent>().getTexture(), texSize);
			}
			else if (component->name == "Character Controller")
			{
				ImGui::DragScalar("Speed", ImGuiDataType_Float, &currentSelectedEntity->getComponent<CharacterController>().GetSpeed(), 0.05f, &f_min, &f_max, "%f", 1.0f);
			}
			ImGui::Text("");
		}
	}
	else
	{
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "No Entity Selected");
	}
	ImGui::End();
}