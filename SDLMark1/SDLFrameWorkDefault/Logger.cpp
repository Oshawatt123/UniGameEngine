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
		if (verbosity == ERROR)
		{
			std::cout << "[ERROR]" << message << std::endl;
		}
		else if (verbosity == DEBUG)
		{
			std::cout << "[DEBUG]" << message << std::endl;
		}
		else if (verbosity == WARNING)
		{
			std::cout << "[WARNING]" << message << std::endl;
		}
		else
		{
			std::cout << message << std::endl;
		}
	}
}

Logger::Logger()
{
}

Logger::~Logger()
{
}