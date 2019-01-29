#include "Light.h"


Light::Light()
{
	direction = Vector3(0.0f, 0.0f, 0.0f);
	color = Vector3(1.0f, 1.0f, 1.0f);
	intensity = 1.0f;
}

void Light::SetDirection(float x, float y, float z)
{
	direction = Vector3(x, y, z);
}

void Light::SetColor(float r, float g, float b)
{
	if (r > 1.0f)
	{
		r = 1.0f;
	}
	else if (r < 0.0f)
	{
		r = 0.0f;
	}

	if (g > 1.0f)
	{
		g = 1.0f;
	}
	else if (g < 0.0f)
	{
		g = 0.0f;
	}

	if (b > 1.0f)
	{
		b = 1.0f;
	}
	else if (b < 0.0f)
	{
		b = 0.0f;
	}

	color = Vector3(r, g, b);
}

void Light::SetIntensity(float value)
{
	intensity = value;
}

Vector3 & Light::GetDirection()
{
	return direction;
}

Vector3 & Light::GetColor()
{
	return color;
}

float & Light::GetIntensity()
{
	return intensity;
}
