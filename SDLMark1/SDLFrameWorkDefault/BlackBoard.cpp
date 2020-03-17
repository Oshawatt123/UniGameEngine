#include "BlackBoard.h"

BlackBoard* BlackBoard::bb = 0; // NULL

BlackBoard* BlackBoard::Instance()
{
	if (bb == 0) // NULL
	{
		bb = new BlackBoard();
	}
	return bb;
}

int BlackBoard::getIDNumber()
{
	return IDNumber++;
}

BlackBoard::BlackBoard()
{
}

BlackBoard::~BlackBoard()
{
}