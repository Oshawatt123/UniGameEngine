#pragma once

#include <vector>

#include "Timer.h"

/*!
 The Time class used to handle all things time in the Filthy Engine
 Primarily useful for calculating delta-time to ensure frame-independent running of the game
*/
class Time
{
public:
private:
	static Time* sInstance; /*!< Static instance of the Time class. */

public:

	float deltaTime; /*!< Last frame's delta time*/
	float deltaTimes[100]; /*!< An array of the past 100 frames' delta time for displaying on a graph*/

	int index = 0;

	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;

	Time();

	/*!
		Method for getting an instance of Time.
	*/
	static Time* Instance();

	/*!
		Denotes the start of a new frame.
	*/
	void NewFrame();

	/*!
		Denotes the end of a frame, and calculates the deltaTime.
	*/
	float EndFrame();
};