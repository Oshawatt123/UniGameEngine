#pragma once

#include "EngineStructs.h"

#include <string>
#include <iostream>

class Logger
{
private:
	static Logger* sInstance;
	int mVerbosity = NOTHING;

public:
	static Logger* Instance();

	void LogString(std::string message, Verbosity verbosity);

private:
	Logger();
	~Logger();
};