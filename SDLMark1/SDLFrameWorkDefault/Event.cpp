#include "Event.h"

Event::Event(FilthyEventType _eventType, std::string data)
{
	eventType = _eventType;
	stringData = data;
}
