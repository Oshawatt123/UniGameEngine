#pragma once
class BlackBoard
{
private:
	static BlackBoard* bb;

	int IDNumber;

public:
	static BlackBoard* Instance();
	static void Release();

	int getIDNumber();


	bool EditMode;

private:
	BlackBoard();
	~BlackBoard();
};

