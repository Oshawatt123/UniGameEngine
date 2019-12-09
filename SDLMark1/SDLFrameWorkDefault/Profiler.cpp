#include "Profiler.h"

void Profiler::StartProfile()
{
	timer = clock();
}

void Profiler::EndProfile()
{
	long double duration = (long double)(clock() - timer);
	duration = duration / (double)CLOCKS_PER_SEC;
	Log(std::to_string(duration), DEBUG);
}