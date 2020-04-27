#pragma once
#include <SDL.h>
#include<iostream>
#include "imgui.h"
#include "imgui_impl_sdl.h"

#include "EngineStructs.h"
class InputManager
{
private:
	static InputManager* sInstance; /*!< Static instance of the Time class. */

	const Uint8* mKeyBoardStates; /*!< the current state of the keyboard this frame, stored as an integer for bitmasking.*/
	bool WindowIsQuit; /*!< A bool for if the window has been closed.*/

	
	int prevMouseX, prevMouseY; /*!< Used for calculated mouse delta movement.*/
	int prevMouseButtons; /*!< Used for calculating mouse press down and up.*/

public:
	int mouseButtons; /*!< the current state of the mouse buttons this frame.*/
	int mouseX, mouseY; /*!< the current x and y positions of the mouse.*/
	int mouseWheel; /*!< the current state of the mouse wheel.*/
	int mouseDeltaX, mouseDeltaY; /*!< the calculated mouse delta movement for this frame.*/

	/*!
		Method for getting an instance of Time.
	*/
	static InputManager* Instance();

	/*!
		Cleans up the Input Manager
	*/
	static void Release();

	/*!
		Checks whether a specific key has been pressed.

		\param[in] scanCode	The SDL_Scancode for the key we want to check has been pressed.

		\return whether or not the key has been pressed.
	*/
	bool KeyDown(SDL_Scancode scanCode);
	//bool KeyUp(SDL_Scancode scanCode);

	/*!
		Checks whether a specific mouse button has been pressed.

		\param[in] mouseButton	The mouse button that we want to check. 0 for left, 1 for right, 2 for middle.

		\return whether or not the mouse button has been pressed.
	*/
	bool MouseDown(int mouseButton);
	//bool MouseUp(int mouseButton);

	/*!
		Getter function for if the window has been closed.

		\return Whether or not the window has been closed.
	*/
	bool WindowQuit();

	/*!
		Updates the Input Manager.

		Here, all the input is gotten from SDL. Keyboard is updated, mouse input is updated and mouse delta is calculated.
	*/
	void Update();

private:

	InputManager();
	~InputManager();
};