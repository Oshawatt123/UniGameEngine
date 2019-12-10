#pragma once

#include "EngineStructs.h"

#include <string>
#include <iostream>

class Logger
{
private:
	static Logger* sInstance;
	int mVerbosity = ERROR;

public:
	static Logger* Instance();

	void LogString(std::string message, Verbosity verbosity);

private:
	Logger();
	~Logger();
};