#pragma once
#include <time.h>
#include "EngineStructs.h"
#include "Logger.h"

class Profiler
{
private:
	clock_t timer;

public:
	void StartProfile();
	void EndProfile();
};