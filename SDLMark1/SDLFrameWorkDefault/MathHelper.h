#pragma once
#include <math.h>
#include "SDL.h"

class Vector2
{
private:
	float magnitude = 0;
public:

	float x;
	float y;

	float& getXAddr() { return x; }
	float& getYAddr() { return y; }

	Vector2();
	Vector2(float x, float y);

	// const because we aren't changing vec, and & because we don't want to copy
	Vector2& Add(const Vector2& vec);
	Vector2& Subtract(const Vector2& vec);
	Vector2& Multiply(const Vector2& vec);
	Vector2& Divide(const Vector2& vec);
	Vector2& Multiply(const float& value);
	Vector2& Divide(const float& value);

	friend Vector2& operator+(Vector2& v1, const Vector2& v2);
	friend Vector2& operator-(Vector2& v1, const Vector2& v2);
	friend Vector2& operator*(Vector2& v1, const Vector2& v2);
	friend Vector2& operator/(Vector2& v1, const Vector2& v2);
	friend Vector2& operator*(Vector2& v1, const float& value);
	friend Vector2& operator/(Vector2& v1, const float& value);

	Vector2& operator+=(const Vector2& vec);
	Vector2& operator-=(const Vector2& vec);
	Vector2& operator*=(const Vector2& vec);
	Vector2& operator/=(const Vector2& vec);

	Vector2& operator*=(const float& value);
	Vector2& operator/=(const float& value);

	void Normalize();
	float Magnitude();

};

struct Line
{
	Vector2 start;
	Vector2 end;
	SDL_Color color;

	Line(int x1, int y1, int x2, int y2, SDL_Color _color = { 0,0,0,255 })
	{
		start = Vector2(x1, y1);
		end = Vector2(x2, y2);
		color = _color;
	}

	Line(Vector2 _start, Vector2 _end, SDL_Color _color = { 0,0,0,255 })
	{
		start = _start;
		end = _end;
		color = _color;
	}
};