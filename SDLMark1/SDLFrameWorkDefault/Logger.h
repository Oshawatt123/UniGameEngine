#pragma once

#include "EngineStructs.h"

#include <string>
#include <iostream>

/*!
	The logger is a QoL class to allow me to get only the information I need by changing which level of logging I want to perform.
	The enum for the logging levels is in EngineStructs, but can be seen here:

	enum Verbosity
	{
		EVERYONE,
		FILTHY_DEBUG,
		DEBUG,
		WARNING,
		DBERROR,
		NOTHING
	};

	If we are running a verbosity of DEBUG, nothing logged with a verbosity of FILTHY_DEBUG will be printed to the console.
*/
class Logger
{
private:
	static Logger* sInstance; /*!< Static instance of the Logger class. */
	int mVerbosity = DEBUG; /*!< The level of the logging. Everything logged under this verbosity is ignored. Enum for this is in EngineStructs*/

public:

	/*!
		Method for getting an instance of Logger.
	*/
	static Logger* Instance();

	/*!
		Logs a string, with a certain verbosity.

		\param[in] message		The message to log.
		\param[in] verbosity	The verbosity of the log.
	*/
	void LogString(std::string message, Verbosity verbosity);

private:
	Logger();
	~Logger();
};