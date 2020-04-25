#pragma once
#include <SDL.h>
#include<iostream>
#include "imgui.h"
#include "imgui_impl_sdl.h"

#include "EngineStructs.h"
class InputManager
{
private:
	static InputManager* sInstance;

	const Uint8* mKeyBoardStates;
	bool WindowIsQuit;

	
	int prevMouseX, prevMouseY;
	int prevMouseButtons;

public:
	int mouseButtons;
	int mouseX, mouseY;
	int mouseWheel;
	int mouseDeltaX, mouseDeltaY;

	static InputManager* Instance();
	static void Release();

	bool KeyDown(SDL_Scancode scanCode);
	//bool KeyUp(SDL_Scancode scanCode);

	bool MouseDown(int mouseButton);
	bool MouseUp(int mouseButton);

	bool WindowQuit();

	void Update();

private:

	InputManager();
	~InputManager();
};