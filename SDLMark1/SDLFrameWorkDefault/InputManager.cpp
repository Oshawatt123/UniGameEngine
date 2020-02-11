#include "InputManager.h"

InputManager* InputManager::sInstance = NULL;

InputManager* InputManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new InputManager();
	}
	return sInstance;
}

void InputManager::Release()
{
	delete(sInstance);
	sInstance = nullptr;
}

bool InputManager::KeyDown(SDL_Scancode scanCode)
{
	return mKeyBoardStates[scanCode];
}

bool InputManager::WindowQuit()
{
	return WindowIsQuit;
}

void InputManager::Update()
{
	WindowIsQuit = false;
	mKeyBoardStates = SDL_GetKeyboardState(NULL);
	mouseButtons = SDL_GetMouseState(&mouseX, &mouseY);
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		ImGui_ImplSDL2_ProcessEvent(&e);
		if (e.type == SDL_QUIT)
		{
			WindowIsQuit = true;
		}
		else if (e.type == SDL_MOUSEWHEEL)
		{
			mouseWheel = e.wheel.y;
		}
	}
}

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}