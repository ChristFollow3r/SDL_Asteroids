#pragma once
#include <iostream>

struct  Vector2
{
	float x;
	float y;

	//Constructors
	Vector2() : x(0), y(0) {}
	Vector2(float x, float y) : x(x), y(y) {}
	
	Vector2 operator+(Vector2& other) {
		return Vector2(x + other.x, y + other.y);
	}

};
