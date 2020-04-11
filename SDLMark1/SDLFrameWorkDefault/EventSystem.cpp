#include "EventSystem.h"

EventSystem* EventSystem::sInstance = NULL;

EventSystem* EventSystem::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new EventSystem();
	}
	return sInstance;
}

void EventSystem::RaiseEvent(FilthyEventType _type, std::string data)
{
	events.push_back(new Event(_type, data));
}

Event* EventSystem::GetEvent(FilthyEventType _type)
{
	for (Event* x : events)
	{
		// check if we have an event of that type to return
		if (x->eventType == _type)
		{
			// return it and remove it from the vector
			events.erase(std::remove(events.begin(), events.end(), x), events.end());
			return x;
		}
	}
	return nullptr;
}

EventSystem::EventSystem() {};