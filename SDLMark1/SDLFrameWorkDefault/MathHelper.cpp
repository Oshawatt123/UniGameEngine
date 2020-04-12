#include "MathHelper.h"

// Initialization
Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

// Normal Maths functions
Vector2& Vector2::Add(const Vector2& vec)
{
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2& Vector2::Subtract(const Vector2& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2& Vector2::Multiply(const Vector2& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector2& Vector2::Divide(const Vector2& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

Vector2& Vector2::Multiply(const float& value)
{
	this->x *= value;
	this->y *= value;

	return *this;
}

Vector2& Vector2::Divide(const float& value)
{
	this->x /= value;
	this->y /= value;

	return *this;
}

// Normal operator overloading
Vector2& operator+(Vector2& v1, const Vector2& v2)
{
	return v1.Add(v2);
}

Vector2& operator-(Vector2& v1, const Vector2& v2)
{
	return v1.Subtract(v2);
}

Vector2& operator*(Vector2& v1, const Vector2& v2)
{
	return v1.Multiply(v2);
}


Vector2& operator/(Vector2& v1, const Vector2& v2)
{
	return v1.Divide(v2);
}

Vector2& operator*(Vector2& v1, const float& value)
{
	return v1.Multiply(value);
}

Vector2& operator/(Vector2& v1, const float& value)
{
	return v1.Divide(value);
}

// Advanced operator overloading
Vector2& Vector2::operator+=(const Vector2& vec)
{
	return this->Add(vec);
}

Vector2& Vector2::operator-=(const Vector2& vec)
{
	return this->Subtract(vec);
}

Vector2& Vector2::operator*=(const Vector2& vec)
{
	return this->Multiply(vec);
}

Vector2& Vector2::operator/=(const Vector2& vec)
{
	return this->Divide(vec);
}

Vector2& Vector2::operator*=(const float& value)
{
	return this->Multiply(value);
}

Vector2& Vector2::operator/=(const float& value)
{
	return this->Divide(value);
}

// does nothing, needs fixing
void Vector2::Normalize()
{
	magnitude = sqrt((x * x) + (y * y));
	*this /= magnitude;
}