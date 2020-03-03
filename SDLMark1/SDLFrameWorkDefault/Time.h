#pragma once

#include <vector>

#include "Timer.h"
class Time
{
public:
	Timer timer;

	float deltaTime;
	float deltaTimes[100];
	int index = 0;

	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;

	Time();

	void NewFrame();

	float EndFrame();
};