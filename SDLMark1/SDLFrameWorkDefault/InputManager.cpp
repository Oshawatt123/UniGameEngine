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

bool InputManager::MouseDown(int mouseButton)
{
	return mouseButtons && SDL_BUTTON(mouseButton);
}

/*bool InputManager::MouseUp(int mouseButton)
{
	return false;
}*/

bool InputManager::WindowQuit()
{
	return WindowIsQuit;
}

void InputManager::Update()
{
	// set last frames data
	prevMouseX = mouseX;
	prevMouseY = mouseY;
	prevMouseButtons = mouseButtons;

	WindowIsQuit = false;
	mKeyBoardStates = SDL_GetKeyboardState(NULL);
	mouseButtons = SDL_GetMouseState(&mouseX, &mouseY);

	mouseDeltaX = mouseX - prevMouseX;
	mouseDeltaY = mouseY - prevMouseY;

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