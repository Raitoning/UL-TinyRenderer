#pragma once

#include <math.h>

class Vector3
{
private:

	float m_x;
	float m_y;
	float m_z;

public:

	Vector3();
	Vector3(float x, float y, float z);

	Vector3 operator+ (const Vector3& other);
	Vector3 operator- (const Vector3& other);
	Vector3 operator* (float factor);
	float operator*(const Vector3 & other);
	Vector3 operator/ (float factor);
	Vector3 operator^ (const Vector3& other);
	bool operator== (const Vector3& other);

	float GetX();
	float GetY();
	float GetZ();

	void SetX(float value);
	void SetY(float value);
	void SetZ(float value);

	float Magnitude();
	void Normalize();
};

