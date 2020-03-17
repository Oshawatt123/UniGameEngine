#include "Game.h"

void FollowFilePath(std::string path)
{
	// I AM THE BASE CASE
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		std::string pathString = entry.path().string();

		// base case when there are no more folders to look through, as a folder should have no extension
		if (entry.path().has_extension())
		{
			std::string extension = entry.path().extension().string();
			if (extension == ".filthyscene")
			{
				if (ImGui::Button(pathString.c_str()))
				{
					// load a scene from this filePath
					SceneManager::Instance()->LoadSceneByPath(pathString.c_str());
				}
			}
			else if (ImGui::TreeNodeEx(pathString.c_str()))
			{
				ImGui::TreePop();
			}
		}
		else
		{
			if (ImGui::TreeNodeEx(pathString.c_str()))
			{
				// warning : recursive
				FollowFilePath(entry.path().string());
				ImGui::TreePop();
			}
		}
	}
}

SDL_GLContext gl_context;

Game::Game()
{
	_Time = new Time();

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
	editorCamera.x = SCREEN_WIDTH * 0.25;
	editorCamera.y = SCREEN_HEIGHT * 0.05;
	editorCamera.w = RENDER_VIEW_WIDTH;
	editorCamera.h = RENDER_VIEW_HEIGHT;

	// create renderer
	Renderer::Instance(m_Window);

	// create physics engine
	physicsEngine = new PhysicsEngine();

	// create resource manager
	ResourceManager::Instance(Renderer::Instance()->getRenderer());

	SceneManager::Instance(physicsEngine, &editorCamera);

	ImGui::CreateContext();
	ImGuiSDL::Initialize(Renderer::Instance()->getRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT);

	SceneManager::Instance()->LoadSceneByPath("../Assets/Scenes/Level1.filthyscene");

	// ##### hard-coding ##### //


	// replace this with a build list of scenes and load the first one in
	currentSelectedEntity = SceneManager::Instance()->getCurrentScene()->getEntityByName("Player");
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
	_Time->NewFrame();

	UpdateInputManager();

	// set up ImGui input
	ImGuiIO& io = ImGui::GetIO();
	io.DeltaTime = 1.0f / 60.0f;
	mousex = static_cast<float>(InputManager::Instance()->mouseX);
	mousey = static_cast<float>(InputManager::Instance()->mouseY);
	io.MousePos = ImVec2(mousex, mousey);
	io.MouseDown[0] = InputManager::Instance()->mouseButtons & SDL_BUTTON(SDL_BUTTON_LEFT);
	io.MouseDown[1] = InputManager::Instance()->mouseButtons & SDL_BUTTON(SDL_BUTTON_RIGHT);
	//io.MouseWheel = static_cast<float>(InputManager::Instance()->mouseWheel);

	// editor mode
	if (!EditMode)
	{
		// scene tick
		SceneManager::Instance()->getCurrentScene()->Tick();

		// update physics
		physicsEngine->Tick();
	}
	else
	{
		// clicking to view an entity in the inspector
		if ((InputManager::Instance()->mouseButtons && SDL_BUTTON(SDL_BUTTON_LEFT)))
		{
			SceneManager::Instance()->getCurrentScene()->CheckPointCollideEntityScreenSpace(Vector2(mousex, mousey), clickedObject);
			if (clickedObject != nullptr)
			{
				// reset last entities edit mode
				if(currentSelectedEntity)
					 currentSelectedEntity->editMode = false;

				// set new entity and set their edit mode
				currentSelectedEntity = clickedObject;
				currentSelectedEntity->editMode = true;
			}
		}

		SceneManager::Instance()->getCurrentScene()->EditorTick();
	}

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

	DrawScenePicker();

	DrawEngineDebug();

	// Clear Renderer buffer from last frame
	Renderer::Instance()->ClearRenderer();

	// draw the level, and all entities inside it
	SceneManager::Instance()->getCurrentScene()->Draw();

	// render GUI
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());

	// Update the renderer with the newly drawn Sprites
	Renderer::Instance()->UpdateRenderer();

	_Time->EndFrame();
}

void Game::UpdateInputManager(void)
{
	InputManager::Instance()->Update();
}

void Game::DrawHeirarchy()
{
	// Heirarchy Window
	ImGui::Begin("Heirarchy", &heirarchyOpen);
	ImGui::TextColored(ImVec4(1, 0, 1, 1), SceneManager::Instance()->getCurrentScene()->GetName().c_str());

	// populate heirarchy
	if (ImGui::BeginChild("EntityList"))
	{
		ImGui::CheckboxFlags("Double Click to open", (unsigned int*)&treeNodeDoubleClick, ImGuiTreeNodeFlags_OpenOnDoubleClick);
		ImGui::Text("");
		Entity* temp = SceneManager::Instance()->getCurrentScene()->PopulateHeirarchy();
		if (temp)
			currentSelectedEntity = temp;
	}


	ImGui::EndChild();

	ImGui::Text("New entity jazz");
	if (ImGui::BeginPopupContextItem("New Entity"))
	{
		if (ImGui::Selectable("Empty Object"))
		{
			Entity* newEntity = new Entity();
			newEntity->addComponent<PositionComponent>();
			SceneManager::Instance()->getCurrentScene()->AddEntity(newEntity);
		}
		ImGui::EndPopup();
	}
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
			component->PopulateInspector();
			ImGui::Text("");
		}

		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("ComponentAddPopUp");
		if (ImGui::BeginPopup("ComponentAddPopUp"))
		{
			Log("FUNCTION PLEEASSEEEE", DEBUG);
			// FUNCTION PLEASEEEEEEEEEEEEEEE
			if (ImGui::Selectable("Sprite Component"))
				if (currentSelectedEntity->hasComponent<SpriteComponent>() == false)
				{
					currentSelectedEntity->addComponent<SpriteComponent>();
					// we must init due to the nature of how init is called
					currentSelectedEntity->getComponent<SpriteComponent>().Init();
				}
			if (ImGui::Selectable("Collision Component"))
				if (currentSelectedEntity->hasComponent<CollisionComponent>() == false)
				{
					currentSelectedEntity->addComponent<CollisionComponent>();
					// we must init due to the nature of how init is called
					currentSelectedEntity->getComponent<CollisionComponent>().Init();
				}
			if (ImGui::Selectable("Character Controller"))
				if (currentSelectedEntity->hasComponent<CharacterController>() == false)
				{
					currentSelectedEntity->addComponent<CharacterController>();
					// we must init due to the nature of how init is called
					currentSelectedEntity->getComponent<CharacterController>().Init();
				}
			if (ImGui::Selectable("Camera"))
				if (currentSelectedEntity->hasComponent<CameraComponent>() == false)
				{
					currentSelectedEntity->addComponent<CameraComponent>();
					// we must init due to the nature of how init is called
					currentSelectedEntity->getComponent<CameraComponent>().Init();
				}

			ImGui::EndPopup();
		}

	}
	else
	{
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "No Entity Selected");
	}
	ImGui::End();
}

void Game::DrawScenePicker()
{
	ImGui::Begin("Assets", &scenePickerOpen);
	for (const auto& entry : std::filesystem::directory_iterator(assetsPath))
	{
		std::string pathString = entry.path().string();
		std::string pathExtension = entry.path().extension().string();
		std::string fullFile = pathString + pathExtension;
		ImGui::BeginChild("Assets");
		// warning: recursive
		if (entry.path().has_extension())
		{
			if (ImGui::TreeNodeEx(pathString.c_str()))
			{
				ImGui::TreePop();
			}
		}
		else
		{
			if (ImGui::TreeNodeEx(pathString.c_str() ))
			{
				FollowFilePath(entry.path().string());
				ImGui::TreePop();
			}
		}
		ImGui::EndChild();
	}
	ImGui::End();
}

void Game::DrawEngineDebug()
{
	ImGui::Begin("Debug Window", &heirarchyOpen);
	ImGui::Text(std::to_string(mousex).c_str());
	ImGui::Text(std::to_string(mousey).c_str());
	ImGui::Checkbox("EditMode", &EditMode);
 
	ImGui::PlotLines("Frame time", _Time->deltaTimes, IM_ARRAYSIZE(_Time->deltaTimes));
	ImGui::End();
}