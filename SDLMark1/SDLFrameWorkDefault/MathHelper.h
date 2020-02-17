#pragma once
#include <math.h>

class Vector2
{
public:

	float x;
	float y;
	float magnitude = 0;

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

};