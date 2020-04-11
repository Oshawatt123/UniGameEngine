#pragma once
#include <string>
#include "EngineStructs.h"

class Event
{
public:
	std::string stringData;
	int intData;
	float floatData;

	FilthyEventType eventType;


	Event(FilthyEventType _eventType, std::string data);
};

