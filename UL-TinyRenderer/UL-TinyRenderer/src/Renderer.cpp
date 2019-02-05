#include "Renderer.h"
#include <iostream>

#define LOG(X) std::cout << X << std::endl

// Public functions.

Renderer::Renderer(int width, int height)
{
	m_width = width;
	m_height = height;

	m_renderOutput = TGAImage(m_width, m_height, TGAImage::Format::RGB);
	m_zBuffer = std::vector<float>(m_width * m_height);

	std::fill(m_zBuffer.begin(), m_zBuffer.end(), std::numeric_limits<float>().max());
}

void Renderer::RenderWireframe(OBJFile& file)
{
	std::vector<Vector3> vertices = file.GetVertices();
	std::vector<Vector3> faces = file.GetFaces();

	for (Vector3 v : faces)
	{
		RenderLine(((vertices[v.GetX() - 1].GetX() + 1.f) / 2) * m_width,
			((vertices[v.GetX() - 1].GetY() + 1.f) / 2) * m_width,
			((vertices[v.GetY() - 1].GetX() + 1.f) / 2) * m_width,
			((vertices[v.GetY() - 1].GetY() + 1.f) / 2) * m_width
		);

		RenderLine(((vertices[v.GetX() - 1].GetX() + 1.f) / 2) * m_width,
			((vertices[v.GetX() - 1].GetY() + 1.f) / 2) * m_width,
			((vertices[v.GetZ() - 1].GetX() + 1.f) / 2) * m_width,
			((vertices[v.GetZ() - 1].GetY() + 1.f) / 2) * m_width
		);

		RenderLine(((vertices[v.GetY() - 1].GetX() + 1.f) / 2) * m_width,
			((vertices[v.GetY() - 1].GetY() + 1.f) / 2) * m_width,
			((vertices[v.GetZ() - 1].GetX() + 1.f) / 2) * m_width,
			((vertices[v.GetZ() - 1].GetY() + 1.f) / 2) * m_width
		);
	}
}

void Renderer::RenderFile(OBJFile& file)
{
	std::vector<Vector3> vertices = file.GetVertices();
	std::vector<Vector3> faces = file.GetFaces();

	for (Vector3 v : faces)
	{
		Vector3 a(static_cast<int>(((vertices[v.GetX() - 1].GetX() + 1.f) / 2) * m_width + .5f),
			static_cast<int>(((vertices[v.GetX() - 1].GetY() + 1.f) / 2) * m_width + .5f),
			((vertices[v.GetX() - 1].GetZ() + 1.f) / 2) * m_width
		);

		Vector3 b(static_cast<int>(((vertices[v.GetY() - 1].GetX() + 1.f) / 2) * m_width + .5f),
			static_cast<int>(((vertices[v.GetY() - 1].GetY() + 1.f) / 2) * m_width + .5f),
			((vertices[v.GetY() - 1].GetZ() + 1.f) / 2) * m_width
		);

		Vector3 c(static_cast<int>(((vertices[v.GetZ() - 1].GetX() + 1.f) / 2) * m_width + .5f),
			static_cast<int>(((vertices[v.GetZ() - 1].GetY() + 1.f) / 2) * m_width + .5f),
			((vertices[v.GetZ() - 1].GetZ() + 1.f) / 2) * m_width
		);

		float redIntensity = 0.0f;
		float greenIntensity = 0.0f;
		float blueIntensity = 0.0f;

		for (Light l : m_lights)
		{
			float lightIntensity = Lighting(a, b, c, l);

			if (lightIntensity > 0.0f)
			{
				redIntensity += lightIntensity * l.GetColor().GetX() * l.GetIntensity();
				greenIntensity += lightIntensity * l.GetColor().GetY() * l.GetIntensity();
				blueIntensity += lightIntensity * l.GetColor().GetZ() * l.GetIntensity();
			}
		}


		if (redIntensity > 0.0f || greenIntensity > 0.0f || blueIntensity > 0.0f)
		{
			if (redIntensity > 1.0f)
			{
				redIntensity = 1.0f;
			}
			if (greenIntensity > 1.0f)
			{
				greenIntensity = 1.0f;
			}
			if (blueIntensity > 1.0f)
			{
				blueIntensity = 1.0f;
			}
			TGAColor color(redIntensity * 255, greenIntensity * 255, blueIntensity * 255);
			RenderTriangle(a, b, c, color);
		}
	}


	// Drawing the zBuffer.
	//for (int y = 0; y < m_height; y++)
	//{
	//	for (int x = 0; x < m_width; x++)
	//	{
	//		TGAColor zColor(m_zBuffer[x + y * m_width], m_zBuffer[x + y * m_width], m_zBuffer[x + y * m_width]);
	//		m_renderOutput.set(x, y, zColor);
	//	}
	//}
}

void Renderer::SaveRender(const char * fileName)
{
	m_renderOutput.flip_vertically();
	m_renderOutput.write_tga_file(fileName);
}

void Renderer::AddLight(Light& light)
{
	m_lights.push_back(light);
}

// Private functions.

void Renderer::RenderLine(int x1, int y1, int x2, int y2)
{
	bool swapped = false;

	// If the line is higher than longer,
	// Make it longer than higher.
	if (std::abs(x1 - x2) < std::abs(y1 - y2))
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
		swapped = true;
	}

	// If the first point is at the right of the second point,
	// swap the two point coordinates for the loop.
	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	for (int x = x1; x <= x2; x++)
	{
		// Linear interpolation.
		float t = (float)(x - x1) / (float)(x2 - x1);
		int y = y1 * (1.0f - t) + y2 * t;

		// If the coordinates have been swapped, swap them again.
		if (swapped)
		{
			m_renderOutput.set(y, x, white);
		}
		else
		{
			m_renderOutput.set(x, y, white);
		}
	}
}

float Renderer::Lighting(Vector3& a, Vector3& b, Vector3& c, Light& light)
{
	Vector3 ab = b - a;
	Vector3 ac = c - a;

	Vector3 normal = ab ^ ac;

	normal.Normalize();

	float dot = normal.GetX() * light.GetDirection().GetX() +
		normal.GetY() * light.GetDirection().GetY() +
		normal.GetZ() * light.GetDirection().GetZ();

	return dot;
}

Vector3 Renderer::BarycentricCoordinates(Vector3 & a, Vector3 & b, Vector3 & c, Vector3 & p)
{
	Vector3 ab = b - a;
	Vector3 ac = c - a;
	Vector3 pa = a - p;

	Vector3 x(ac.GetX(), ab.GetX(), pa.GetX());
	Vector3 y(ac.GetY(), ab.GetY(), pa.GetY());

	Vector3 cross = x ^ y;

	if (cross.GetZ() < 0.0f)
	{
		return Vector3(-1, -1, -1);
	}

	Vector3 barycentrics(
		1.0f - (cross.GetX() + cross.GetY()) / cross.GetZ(),
		cross.GetY() / cross.GetZ(),
		cross.GetX() / cross.GetZ()
	);

	return barycentrics;
}

void Renderer::RenderTriangle(Vector3& a, Vector3& b, Vector3& c, TGAColor& color)
{
	int xMin = MinCoordinates(a.GetX(), b.GetX(), c.GetX());
	int yMin = MinCoordinates(a.GetY(), b.GetY(), c.GetY());
	int xMax = MaxCoordinates(a.GetX(), b.GetX(), c.GetX());
	int yMax = MaxCoordinates(a.GetY(), b.GetY(), c.GetY());

	for (int x = xMin; x < xMax; x++)
	{
		for (int y = yMin; y < yMax; y++)
		{
			Vector3 point(x, y, 0);

			Vector3 depth = BarycentricCoordinates(a, b, c, point);

			if (depth.GetX() >= 0 && depth.GetY() >= 0 && depth.GetZ() >= 0)
			{
				float z = a.GetZ() * depth.GetX();
				z += b.GetZ() * depth.GetY();
				z += c.GetZ() * depth.GetZ();

				if (z < m_zBuffer[x + y * m_width])
				{
					m_zBuffer[x + y * m_width] = z;
					m_renderOutput.set(x, y, color);
				}
			}
		}
	}
}

float Renderer::MinCoordinates(float a, float b, float c)
{
	float min;

	a < b ? min = a : min = b;
	min < c ? min = min : min = c;

	return min;
}

float Renderer::MaxCoordinates(float a, float b, float c)
{
	float max;

	a > b ? max = a : max = b;
	max > c ? max = max : max = c;

	return max;
}

// Legacy triangle drawing method via line sweeping.

//// TODO: Fix my own code instead of using the teacher's one.
//// TODO: Fix artefacts.
//void Renderer::RenderTriangle(Vector3& a, Vector3& b, Vector3& c, TGAColor& color)
//{
//	if (b.GetY() > a.GetY())
//	{
//		std::swap(b, a);
//	}
//	if (c.GetY() > a.GetY())
//	{
//		std::swap(c, a);
//	}
//	if (c.GetY() > b.GetY())
//	{
//		std::swap(b, c);
//	}
//
//	float height = a.GetY() - c.GetY();
//
//	//float x;
//
//	//if (c.GetX() > a.GetX())
//	//{
//	//	x = (a.GetX() - c.GetX()) * ((b.GetY() - c.GetY()) / (a.GetY() - c.GetY()));
//	//	x += c.GetX();
//	//}
//	//else
//	//{
//	//	x = (c.GetX() - a.GetX()) * ((b.GetY() - c.GetY()) / (a.GetY() - c.GetY()));
//	//	x += a.GetX();
//	//}
//
//	//Vector3 d(x,
//	//	b.GetY(),
//	//	(a.GetZ() - c.GetZ()) * (b.GetY() - c.GetY()) / (a.GetY() - c.GetY())
//	//);
//
//	float partHeight = b.GetY() - c.GetY() + 1.0f;
//	//for (int i = c.GetY(); i <= b.GetY(); i++)
//	//{
//	//	float t = (float)(i - c.GetY()) / (float)(b.GetY() - c.GetY());
//	//	float xMin = c.GetX() * (1.0f - t) + b.GetX() * t;
//	//	float xMax = c.GetX() * (1.0f - t) + (d.GetX() * t);
//
//	//	if (xMin > xMax)
//	//	{
//	//		std::swap(xMin, xMax);
//	//	}
//
//	//	for (int x = xMin; x <= xMax; x++)
//	//	{
//	//		m_renderOutput.set(x, i, color);
//	//	}
//	//}
//
//	for (int y = c.GetY(); y <= b.GetY(); y++)
//	{
//		float alpha = (float)(y - c.GetY()) / height;
//		float beta = (float)(y - c.GetY()) / partHeight;
//
//		float xMin = c.GetX() + (a.GetX() - c.GetX()) * alpha;
//		float xMax = c.GetX() + (b.GetX() - c.GetX()) * beta;
//
//		if (xMin > xMax)
//		{
//			std::swap(xMin, xMax);
//		}
//
//		for (int x = xMin; x <= xMax; x++)
//		{
//			m_renderOutput.set(x, y, color);
//		}
//	}
//
//	partHeight = a.GetY() - b.GetY() + 1.0f;
//	for (int y = b.GetY(); y <= a.GetY(); y++)
//	{
//		float alpha = (float)(y - c.GetY()) / height;
//		float beta = (float)(y - b.GetY()) / partHeight;
//
//		float xMin = c.GetX() + (a.GetX() - c.GetX()) * alpha;
//		float xMax = b.GetX() + (a.GetX() - b.GetX()) * beta;
//
//		if (xMin > xMax)
//		{
//			std::swap(xMin, xMax);
//		}
//
//		for (int x = xMin; x <= xMax; x++)
//		{
//			m_renderOutput.set(x, y, color);
//		}
//	}
//
//	//for (int i = a.GetY(); i >= b.GetY(); i--)
//	//{
//	//	float t = (float)(i - a.GetY()) / (float)(d.GetY() - a.GetY());
//	//	float xMin = a.GetX() * (1.0f - t) + b.GetX() * t;
//	//	float xMax = a.GetX() * (1.0f - t) + (d.GetX() * t);
//
//	//	if (xMin > xMax)
//	//	{
//	//		std::swap(xMin, xMax);
//	//	}
//
//	//	for (int x = xMin; x <= xMax; x++)
//	//	{
//	//		m_renderOutput.set(x, i, color);
//	//	}
//	//}
//}
