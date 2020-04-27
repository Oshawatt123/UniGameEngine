#pragma once
#include <chrono>
/**
* A simple class which starts timing on creation, and generates a time alive on destruction
*
*/
class Timer
{
public:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;

	/*!
		Starts the timer.
	*/
	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	/*!
		End the timer.
	*/
	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
	}
};