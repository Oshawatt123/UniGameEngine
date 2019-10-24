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
	mKeyBoardStates = SDL_GetKeyboardState(NULL);
}



InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}
