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

void InputManager::Update()
{
	//SDL_PumpEvents();
	mKeyBoardStates = SDL_GetKeyboardState(NULL);
	SDL_Event ev;
	while(SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_QUIT)
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
