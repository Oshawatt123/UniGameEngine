#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <string>

struct Position
{
	int x;
	int y;
};

struct Sprite
{
	std::string filePath;
	bool Transparency;
};

struct Velocity
{
	int vx;
	int vy;
};

#endif // COMPONENTS_H