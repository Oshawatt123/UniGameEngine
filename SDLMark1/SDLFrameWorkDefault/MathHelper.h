#pragma once
#include <math.h>
#include "SDL.h"

/*!
	Vector2 is a class to help with 2D maths.
	Without it, using the engine is incredibly painful.
*/
class Vector2
{
private:
	float magnitude = 0;/*!< A stored value for the magnitude of the Vector. */
public:

	float x; /*!< The x value of the vector. */
	float y; /*!< Theyx value of the vector. */

	float& getXAddr() { return x; } /*!< A reference to the x value of the vector. Some functions require the address to be passed in. */
	float& getYAddr() { return y; }	/*!< A reference to the y value of the vector. Some functions require the address to be passed in. */

	/*!
		Base constructor defaults to (0,0).
	*/
	Vector2();

	/*!
		Override constructor takes an x and y for the vector.
		\param[in] x The x value of the vector.
		\param[in] x The y value of the vector.
	*/
	Vector2(float x, float y);

	// const because we aren't changing vec, and & because we don't want to copy

	/*!
		Adds a vector to THIS vector.
		\param[in] vec The vector to add to THIS vector.
	*/
	Vector2& Add(const Vector2& vec);

	/*!
		Subtracts a vector to THIS vector.
		\param[in] vec The vector to subtract to THIS vector.
	*/
	Vector2& Subtract(const Vector2& vec);

	/*!
		Multiplies THIS vector with a vector.
		\param[in] vec The vector to multiply THIS vector with.
	*/
	Vector2& Multiply(const Vector2& vec);

	/*!
		Divides THIS vector with a vector.
		\param[in] vec The vector to divide THIS vector with.
	*/
	Vector2& Divide(const Vector2& vec);

	/*!
		Multiplies THIS vector with a float.
		\param[in] value The float to multiply THIS vector with.
	*/
	Vector2& Multiply(const float& value);

	/*!
		Divides THIS vector with a float.
		\param[in] value The float to divide THIS vector with.
	*/
	Vector2& Divide(const float& value);

	friend Vector2& operator+(Vector2& v1, const Vector2& v2);	/*!< Overrides the + operator.*/
	friend Vector2& operator-(Vector2& v1, const Vector2& v2);	/*!< Overrides the - operator.*/
	friend Vector2& operator*(Vector2& v1, const Vector2& v2);	/*!< Overrides the * operator.*/
	friend Vector2& operator/(Vector2& v1, const Vector2& v2);	/*!< Overrides the / operator.*/
	friend Vector2& operator*(Vector2& v1, const float& value);	/*!< Overrides the * operator for float multiplication.*/
	friend Vector2& operator/(Vector2& v1, const float& value);	/*!< Overrides the / operator for float division.*/

	Vector2& operator+=(const Vector2& vec); /*!< Overrides the += operator.*/
	Vector2& operator-=(const Vector2& vec); /*!< Overrides the -= operator.*/
	Vector2& operator*=(const Vector2& vec); /*!< Overrides the *= operator.*/
	Vector2& operator/=(const Vector2& vec); /*!< Overrides the /= operator.*/

	Vector2& operator*=(const float& value); /*!< Overrides the *= operator for float multiplication.*/
	Vector2& operator/=(const float& value); /*!< Overrides the /= operator for float division.*/

	void Normalize(); /*!< Normalizes THIS vector.*/

	/*!
		Calculates the magnitude.
		\return The magnitude of this vector as a float
	*/
	float Magnitude();

};

/*!
	A struct to help with drawing debug lines in FilthyEngine.
	A Line is defined by a 2 Vector2's for the start and end of the lines, treated as position co-ordinates in world-space as well as a color.
*/
struct Line
{
	Vector2 start;		/*!< The Start of the line, treated as a position in world-space.*/
	Vector2 end;		/*!< The End of the line, treated as a position in world-space.*/
	SDL_Color color;	/*!< The color of the line.*/

	/*!
		Creates a line.
		\param x1		The x position to start the line in world-space.
		\param y1		The y position to start the line in world-space.
		\param x2		The x position to end the line in world-space.
		\param y2		The y position to end the line in world-space.
		\param _color	The color of the line, defaulted at black.
	*/
	Line(int x1, int y1, int x2, int y2, SDL_Color _color = { 0,0,0,255 })
	{
		start = Vector2(x1, y1);
		end = Vector2(x2, y2);
		color = _color;
	}

	/*!
		Override of the base constructor to take 2 Vector2's for start and end position.
		\param _start	Vector2 for the start of the line in world-space.
		\param _end		Vector2 for the end of the line in world-space.
		\param _color	The color of the line, defaulted at black.
	*/
	Line(Vector2 _start, Vector2 _end, SDL_Color _color = { 0,0,0,255 })
	{
		start = _start;
		end = _end;
		color = _color;
	}
};