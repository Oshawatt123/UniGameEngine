#pragma once
#include <vector>
#include <string>
#include <algorithm>

#include "Time.h"
#include "Event.h"
#include "EngineStructs.h"


class EventSystem
{
private:
	static EventSystem* sInstance;
	static int eventID;
	std::vector<Event*> events;

public:
	static EventSystem* Instance();

	void RaiseEvent(FilthyEventType _type, std::string data);
	Event* GetEvent(FilthyEventType _type);

private:
	EventSystem();
};