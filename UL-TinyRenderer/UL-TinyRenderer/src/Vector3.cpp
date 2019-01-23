#include "Vector3.h"

Vector3::Vector3()
{
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


Vector3::~Vector3()
{
}

Vector3 Vector3::operator+(const Vector3& other)
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other)
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(float factor)
{
	return Vector3(x * factor, y * factor, z * factor);
}

Vector3 Vector3::operator/(float factor)
{
	return Vector3(x /factor, y / factor, z / factor);
}

bool Vector3::operator==(const Vector3& other)
{
	return x == other.x && y == other.y && z == other.z;
}

float Vector3::getX()
{
	return x;
}

float Vector3::getY()
{
	return y;
}

float Vector3::getZ()
{
	return z;
}

float Vector3::magnitude()
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}
