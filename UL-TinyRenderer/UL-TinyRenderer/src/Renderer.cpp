#include "Renderer.h"

Renderer::Renderer(int width, int height)
{
	m_width = width;
	m_height = height;

	m_renderOutput = TGAImage(m_width, m_height, TGAImage::Format::RGB);
}

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
		if (swapped) {

			m_renderOutput.set(y, x, white);
		}
		else
		{
			m_renderOutput.set(x, y, white);
		}
	}
}

void Renderer::saveRender(const char * fileName)
{
	m_renderOutput.write_tga_file(fileName);
}
