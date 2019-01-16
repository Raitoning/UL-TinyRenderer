#pragma once
class Vector3
{
private:

	float x;
	float y;
	float z;

public:

	Vector3(float x, float y, float z);
	~Vector3();

	float getX();
	float getY();
	float getZ();
};

