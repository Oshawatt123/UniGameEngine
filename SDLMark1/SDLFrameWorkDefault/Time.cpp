#include "Time.h"

Time::Time()
{
}

void Time::NewFrame()
{
	start = std::chrono::high_resolution_clock::now();
}

float Time::EndFrame()
{
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;
	deltaTime = duration.count();
	deltaTimes[index] = deltaTime;
	index++;
	if (index >= 100)
	{
		index = 0;
	}
	return deltaTime;
}
