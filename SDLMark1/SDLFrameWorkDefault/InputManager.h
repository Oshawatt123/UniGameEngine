#pragma once
#include <SDL.h>
#include <unordered_map>
#include<iostream>

#include "EngineStructs.h"
class InputManager
{
private:
	static InputManager* sInstance;

	const Uint8* mKeyBoardStates;
	const Uint8* mWindowStates;

public:
	static InputManager* Instance();
	static void Release();

	bool KeyDown(SDL_Scancode scanCode);
	bool WindowEvent(int eventCode);

	void Update();

private:

	InputManager();
	~InputManager();
};