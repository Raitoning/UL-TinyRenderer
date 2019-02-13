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

	std::fill(m_zBuffer.begin(), m_zBuffer.end(), std::numeric_limits<float>().min());

	m_ambientLighting = Vector3(0, 0, 0);
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
	std::vector<Vector3> textels = file.GetTextels();
	std::vector<Vector3> texturesCoordinates = file.GetTextureCoordinates();

	int i = 0;

	for (Vector3 vec : faces)
	{
		Vector3 a(static_cast<int>(((vertices[vec.GetX() - 1].GetX() + 1.f) / 2) * m_width + .5f),
			static_cast<int>(((vertices[vec.GetX() - 1].GetY() + 1.f) / 2) * m_width + .5f),
			(((vertices[vec.GetX() - 1].GetZ() + 1.f) / 2) * m_width + .5f)
		);

		Vector3 b(static_cast<int>(((vertices[vec.GetY() - 1].GetX() + 1.f) / 2) * m_width + .5f),
			static_cast<int>(((vertices[vec.GetY() - 1].GetY() + 1.f) / 2) * m_width + .5f),
			(((vertices[vec.GetY() - 1].GetZ() + 1.f) / 2) * m_width + .5f)
		);

		Vector3 c(static_cast<int>(((vertices[vec.GetZ() - 1].GetX() + 1.f) / 2) * m_width + .5f),
			static_cast<int>(((vertices[vec.GetZ() - 1].GetY() + 1.f) / 2) * m_width + .5f),
			(((vertices[vec.GetZ() - 1].GetZ() + 1.f) / 2) * m_width + .5f)
		);

		Vector3 u = texturesCoordinates[textels[i].GetX() - 1];
		Vector3 v = texturesCoordinates[textels[i].GetY() - 1];
		Vector3 w = texturesCoordinates[textels[i].GetZ() - 1];

		float redIntensity = m_ambientLighting.GetX();
		float greenIntensity = m_ambientLighting.GetY();
		float blueIntensity = m_ambientLighting.GetZ();

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
			Vector3 color(redIntensity, greenIntensity, blueIntensity);
			RenderTriangle(a, b, c, u, v, w, color);
		}
		i++;
	}

	// SaveRender("Output.tga");

	// Drawing the zBuffer for debug purposes.
	// The zBuffer needs to be normalized before output.
	// float max = std::numeric_limits<float>::min();
	//for (int y = 0; y < m_height; y++)
	//{
	//	for (int x = 0; x < m_width; x++)
	//	{
	//		if (m_zBuffer[x + y * m_width] > max)
	//		{
	//			max = m_zBuffer[x + y * m_width];
	//		}
	//	}
	//}

	//for (int y = 0; y < m_height; y++)
	//{
	//	for (int x = 0; x < m_width; x++)
	//	{
	//		TGAColor zColor(
	//			(m_zBuffer[x + y * m_width] / max) * 255,
	//			(m_zBuffer[x + y * m_width] / max) * 255,
	//			(m_zBuffer[x + y * m_width] / max) * 255
	//		);

	//		m_renderOutput.set(x, y, zColor);
	//	}
	//}
	//SaveRender("zBuffer.tga");
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

void Renderer::SetAmbientLighting(float r, float g, float b)
{
	m_ambientLighting = Vector3(r, g, b);
}

void Renderer::SetDiffuseTexture(TGAImage texture)
{
	m_diffuseTexture = texture;
	m_diffuseTexture.flip_vertically();
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

	Vector3 normal = ac ^ ab;

	normal.Normalize();

	float intensity = normal * light.GetDirection();

	return intensity;
}

// Function from StackOverflow.
// I was running out of time and spent hours in debugging,
// and I needed to fix my issues as fast as possible.
// https://stackoverflow.com/questions/25385361/point-within-a-triangle-barycentric-co-ordinates
Vector3 Renderer::BarycentricCoordinates(Vector3 & a, Vector3 & b, Vector3 & c, Vector3 & p)
{
	Vector3 ac = c - a;
	Vector3 bc = c - b;
	Vector3 ca = a - c;
	Vector3 cb = b - c;
	Vector3 cp = p - c;

	float det = cb.GetY() * ca.GetX() + bc.GetX() * ca.GetY();
	float factor_alpha = cb.GetY() * cp.GetX() + bc.GetX() * cp.GetY();
	float factor_beta = ac.GetY() * cp.GetX() + ca.GetX() * cp.GetY();
	float alpha = factor_alpha / det;
	float beta = factor_beta / det;
	float gamma = 1.0f - alpha - beta;

	return Vector3(alpha, beta, gamma);
}

void Renderer::RenderTriangle(Vector3& a, Vector3& b, Vector3& c, Vector3& u, Vector3& v, Vector3& w, Vector3& color)
{
	int xMin = std::min(a.GetX(), std::min(b.GetX(), c.GetX()));
	int yMin = std::min(a.GetY(), std::min(b.GetY(), c.GetY()));
	int xMax = std::max(a.GetX(), std::max(b.GetX(), c.GetX()));
	int yMax = std::max(a.GetY(), std::max(b.GetY(), c.GetY()));

	for (int x = xMin; x < xMax; x++)
	{
		for (int y = yMin; y < yMax; y++)
		{
			Vector3 point(x, y, 1);

			Vector3 depth = BarycentricCoordinates(a, b, c, point);

			if (depth.GetX() >= -0.001f && depth.GetY() >= -0.001f && depth.GetZ() >= -0.001f)
			{
				float z = a.GetZ() * depth.GetX();
				z += b.GetZ() * depth.GetY();
				z += c.GetZ() * depth.GetZ();

				if (z > m_zBuffer[x + y * m_width])
				{
					float uu = u.GetX() * depth.GetX();
					uu += v.GetX() * depth.GetY();
					uu += w.GetX() * depth.GetZ();
					uu *= (float)m_diffuseTexture.get_width();

					float vv = u.GetY() * depth.GetX();
					vv += v.GetY() * depth.GetY();
					vv += w.GetY() * depth.GetZ();
					vv *= (float)m_diffuseTexture.get_height();

					m_zBuffer[x + y * m_width] = z;
					TGAColor diffuse(m_diffuseTexture.get(uu, vv));
					TGAColor finalColor(diffuse[2] * color.GetX(), diffuse[1] * color.GetY(), diffuse[0] * color.GetZ());
					m_renderOutput.set(x, y, finalColor);
				}
			}
		}
	}
}
