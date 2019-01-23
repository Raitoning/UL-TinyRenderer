#include "Renderer.h"

// Public functions.

Renderer::Renderer(int width, int height)
{
	m_width = width;
	m_height = height;

	m_renderOutput = TGAImage(m_width, m_height, TGAImage::Format::RGB);
}

void Renderer::renderWireframe(OBJFile& file)
{
	std::vector<Vector3> vertices = file.getVertices();
	std::vector<Vector3> faces = file.getFaces();

	for (Vector3 v : faces)
	{
		renderLine(((vertices[v.getX() - 1].getX() + 1.f) / 2) * m_width,
			((vertices[v.getX() - 1].getY() + 1.f) / 2) * m_width,
			((vertices[v.getY() - 1].getX() + 1.f) / 2) * m_width,
			((vertices[v.getY() - 1].getY() + 1.f) / 2) * m_width
		);

		renderLine(((vertices[v.getX() - 1].getX() + 1.f) / 2) * m_width,
			((vertices[v.getX() - 1].getY() + 1.f) / 2) * m_width,
			((vertices[v.getZ() - 1].getX() + 1.f) / 2) * m_width,
			((vertices[v.getZ() - 1].getY() + 1.f) / 2) * m_width
		);

		renderLine(((vertices[v.getY() - 1].getX() + 1.f) / 2) * m_width,
			((vertices[v.getY() - 1].getY() + 1.f) / 2) * m_width,
			((vertices[v.getZ() - 1].getX() + 1.f) / 2) * m_width,
			((vertices[v.getZ() - 1].getY() + 1.f) / 2) * m_width
		);
	}

	m_renderOutput.flip_vertically();
}

void Renderer::renderFile(OBJFile& file)
{
	std::vector<Vector3> vertices = file.getVertices();
	std::vector<Vector3> faces = file.getFaces();

	for (Vector3 v : faces)
	{
		Vector3 a(((vertices[v.getX() - 1].getX() + 1.f) / 2) * m_width,
			((vertices[v.getX() - 1].getY() + 1.f) / 2) * m_width,
			((vertices[v.getX() - 1].getZ() + 1.f) / 2) * m_width
		);

		Vector3 b(((vertices[v.getY() - 1].getX() + 1.f) / 2) * m_width,
			((vertices[v.getY() - 1].getY() + 1.f) / 2) * m_width,
			((vertices[v.getY() - 1].getZ() + 1.f) / 2) * m_width
		);

		Vector3 c(((vertices[v.getZ() - 1].getX() + 1.f) / 2) * m_width,
			((vertices[v.getZ() - 1].getY() + 1.f) / 2) * m_width,
			((vertices[v.getZ() - 1].getZ() + 1.f) / 2) * m_width
		);

		TGAColor randomColor(std::rand() * 255, std::rand() * 255, std::rand() * 255);

		renderTriangle(a, b, c, randomColor);
	}
}

void Renderer::saveRender(const char * fileName)
{
	m_renderOutput.flip_vertically();
	m_renderOutput.write_tga_file(fileName);
}

// Private functions.

void Renderer::renderLine(int x1, int y1, int x2, int y2)
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

// TODO: Fix my own code instead of using the teacher's one.
// TODO: Fix artefacts.
void Renderer::renderTriangle(Vector3 a, Vector3 b, Vector3 c, TGAColor color)
{
	if (b.getY() > a.getY())
	{
		std::swap(b, a);
	}
	if (c.getY() > a.getY())
	{
		std::swap(c, a);
	}
	if (c.getY() > b.getY())
	{
		std::swap(b, c);
	}

	float height = a.getY() - c.getY();

	//float x;

	//if (c.getX() > a.getX())
	//{
	//	x = (a.getX() - c.getX()) * ((b.getY() - c.getY()) / (a.getY() - c.getY()));
	//	x += c.getX();
	//}
	//else
	//{
	//	x = (c.getX() - a.getX()) * ((b.getY() - c.getY()) / (a.getY() - c.getY()));
	//	x += a.getX();
	//}

	//Vector3 d(x,
	//	b.getY(),
	//	(a.getZ() - c.getZ()) * (b.getY() - c.getY()) / (a.getY() - c.getY())
	//);

	float partHeight = b.getY() - c.getY() + 1.0f;
	//for (int i = c.getY(); i <= b.getY(); i++)
	//{
	//	float t = (float)(i - c.getY()) / (float)(b.getY() - c.getY());
	//	float xMin = c.getX() * (1.0f - t) + b.getX() * t;
	//	float xMax = c.getX() * (1.0f - t) + (d.getX() * t);

	//	if (xMin > xMax)
	//	{
	//		std::swap(xMin, xMax);
	//	}

	//	for (int x = xMin; x <= xMax; x++)
	//	{
	//		m_renderOutput.set(x, i, color);
	//	}
	//}

	for (int y = c.getY(); y <= b.getY(); y++)
	{
		float alpha = (float)(y - c.getY()) / height;
		float beta = (float)(y - c.getY()) / partHeight;

		float xMin = c.getX() + (a.getX() - c.getX()) * alpha;
		float xMax = c.getX() + (b.getX() - c.getX()) * beta;

		if (xMin > xMax)
		{
			std::swap(xMin, xMax);
		}

		for (int x = xMin; x <= xMax; x++)
		{
			m_renderOutput.set(x, y, color);
		}
	}

	partHeight = a.getY() - b.getY() + 1.0f;
	for (int y = b.getY(); y <= a.getY(); y++)
	{
		float alpha = (float)(y - c.getY()) / height;
		float beta = (float)(y - b.getY()) / partHeight;

		float xMin = c.getX() + (a.getX() - c.getX()) * alpha;
		float xMax = b.getX() + (a.getX() - b.getX()) * beta;

		if (xMin > xMax)
		{
			std::swap(xMin, xMax);
		}

		for (int x = xMin; x <= xMax; x++)
		{
			m_renderOutput.set(x, y, color);
		}
	}

	//for (int i = a.getY(); i >= b.getY(); i--)
	//{
	//	float t = (float)(i - a.getY()) / (float)(d.getY() - a.getY());
	//	float xMin = a.getX() * (1.0f - t) + b.getX() * t;
	//	float xMax = a.getX() * (1.0f - t) + (d.getX() * t);

	//	if (xMin > xMax)
	//	{
	//		std::swap(xMin, xMax);
	//	}

	//	for (int x = xMin; x <= xMax; x++)
	//	{
	//		m_renderOutput.set(x, i, color);
	//	}
	//}
}
