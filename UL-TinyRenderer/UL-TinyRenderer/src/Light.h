#pragma once

#include "Vector3.h"

class Light
{

private:
	Vector3 direction;
	Vector3 color;
	float intensity;

public:
	Light();

	void SetDirection(float x, float y, float z);
	void SetColor(float r, float g, float b);
	void SetIntensity(float value);

	Vector3& GetDirection();
	Vector3& GetColor();
	float& GetIntensity();
};

