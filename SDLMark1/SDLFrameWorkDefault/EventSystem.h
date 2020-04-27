#pragma once
#include <vector>
#include <string>
#include <algorithm>

#include "Time.h"
#include "Event.h"
#include "EngineStructs.h"

/*!
	This is a VERY rudimentary event system.
	It will hold a vector of events and can return an event of a specific FilthyEventType.
	As of writing, the only use of the event system is to decouple Entity from SceneManager and allow the two to interact through the use of events.

	e.g:	Player character collides with the stairs object and raises and event of type SCENE_LOAD and fills the event with the data of the scene it wants to load.
			On the next frame, SceneManager checks for events of type SCENE_LOAD, sees there is one, and processes the event by loading the scene stored in the Event data.

	In general, this class is used to pass data in between systems that normally CAN NOT interact with eachother due to dependancy issues.

	\note This class has been designed to be easily expandable by users, but the Event class is a lot more restrictive with the data it can hold.
*/
class EventSystem
{
private:
	static EventSystem* sInstance; /*!< The instance of EventSystem.*/
	static int eventID; /*!< When new events are generated, they are assigned an ID to keep them distinguishable. This stores the next ID number to be used. They are not re-used.*/
	std::vector<Event*> events; /*!< The vector of Events that have been raised and not processed.*/

public:
	static EventSystem* Instance(); /*!< Method for getting instance of EventSystem.*/

	/*!
		Method for raising an event.
		\param[in] _type	The type of event specified, enum held in EngineStructs.
		\param[in] data		The data to be stored in the event.
	*/
	void RaiseEvent(FilthyEventType _type, std::string data);

	/*!
		Looks throught the events in the events vector. If an event of FilthyEventType _type is found, it is removed from the vector, and returned to the caller.
		\param[in] _type	The event type to search for.
	*/
	Event* GetEvent(FilthyEventType _type);

private:

	EventSystem();
};