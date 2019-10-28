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

bool InputManager::WindowEvent(int eventCode)
{
	return mWindowStates[eventCode];
}

void InputManager::Update()
{
	mKeyBoardStates = SDL_GetKeyboardState(NULL);
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			
		}
	}
}

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}
