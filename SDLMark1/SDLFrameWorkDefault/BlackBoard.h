#pragma once
class BlackBoard
{
private:
	static BlackBoard* bb;/*!< Static instance of the BlackBoard class. */

	int IDNumber;

public:

	/*!
		Method for getting an instance of BlackBoard.
	*/
	static BlackBoard* Instance(); 

	/*!
		Cleans up the blackboard.
	*/
	static void Release();

	/*
		Generates an ID number for entities so they can be uniquely identified. Originally used for ImGui labels but was adopted into the ECS.
		ID numbers are NOT re-used once discarded.

		\return A unique ID number.
	*/
	int getIDNumber();

	/*!
		Blackboard holds a boolean for the state of the engine. All classes which change behaviour if the engine is in edit mode or not, work off of this boolean.
	*/
	bool EditMode;

private:
	BlackBoard();
	~BlackBoard();
};

