#include "Logger.h"

Logger* Logger::sInstance = NULL;

Logger* Logger::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new Logger();
	}
	return sInstance;
}

void Logger::LogString(std::string message, Verbosity verbosity)
{
	if (verbosity >= mVerbosity)
	{
		std::cout << message << std::endl;
	}
}

Logger::Logger()
{
}

Logger::~Logger()
{
}
