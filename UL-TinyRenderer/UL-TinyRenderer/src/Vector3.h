#pragma once

#include <math.h>

class Vector3
{
private:

	float x;
	float y;
	float z;

public:

	Vector3();
	Vector3(float x, float y, float z);
	~Vector3();

	Vector3 operator+ (const Vector3& other);
	Vector3 operator- (const Vector3& other);
	Vector3 operator* (float factor);
	Vector3 operator/(float factor);
	bool operator== (const Vector3& other);

	float getX();
	float getY();
	float getZ();

	float magnitude();
};

