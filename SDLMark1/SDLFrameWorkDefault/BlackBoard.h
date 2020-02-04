#pragma once
class BlackBoard
{
private:
	static BlackBoard* bb;

public:
	static BlackBoard* Instance();
	static void Release();

private:
	BlackBoard();
	~BlackBoard();
};

