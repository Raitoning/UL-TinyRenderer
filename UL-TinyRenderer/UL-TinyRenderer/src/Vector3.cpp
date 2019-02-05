#include "Vector3.h"


Vector3::Vector3()
{
	m_x = 0.0f;
	m_y = 0.0f;
	m_z = 0.0f;
}

Vector3::Vector3(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

Vector3 Vector3::operator+(const Vector3& other)
{
	return Vector3(m_x + other.m_x, m_y + other.m_y, m_z + other.m_z);
}

Vector3 Vector3::operator-(const Vector3& other)
{
	return Vector3(m_x - other.m_x, m_y - other.m_y, m_z - other.m_z);
}

Vector3 Vector3::operator*(float factor)
{
	return Vector3(m_x * factor, m_y * factor, m_z * factor);
}

Vector3 Vector3::operator/(float factor)
{
	return Vector3(m_x /factor, m_y / factor, m_z / factor);
}

Vector3 Vector3::operator^(const Vector3 & other)
{
	return Vector3(
		m_y * other.m_z - m_z * other.m_y,
		m_z * other.m_x - m_x * other.m_z,
		m_x * other.m_y - m_y * other.m_x
	);
}

bool Vector3::operator==(const Vector3& other)
{
	return m_x == other.m_x && m_y == other.m_y && m_z == other.m_z;
}

float Vector3::GetX()
{
	return m_x;
}

float Vector3::GetY()
{
	return m_y;
}

float Vector3::GetZ()
{
	return m_z;
}

float Vector3::Magnitude()
{
	return sqrtf(pow(m_x, 2) + pow(m_y, 2) + pow(m_z, 2));
}

void Vector3::Normalize()
{
	float magnitude = Magnitude();
	m_x = m_x / magnitude;
	m_y = m_y / magnitude;
	m_z = m_z / magnitude;
}
