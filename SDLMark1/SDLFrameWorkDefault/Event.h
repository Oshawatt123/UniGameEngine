#pragma once
#include <string>
#include "EngineStructs.h"

/*!
	The Event class used by EventSystem to store data and pass it between classes that otherwise wouldn't be able to interact.

	An Event is defined by a FilthyEventType, and some data. Events can store some stringData, some intData, and some floatData.
	\note The only FilthyEventType currently is SCENE_LOAD.
*/
class Event
{
public:
	std::string stringData;
	int intData;
	float floatData;

	FilthyEventType eventType;


	Event(FilthyEventType _eventType, std::string data);
};

