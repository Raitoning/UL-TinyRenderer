#pragma once

#include "TGAImage.h"
#include "OBJFile.h"
#include "Light.h"

class Renderer
{
	// Members.
private:

	const TGAColor white = TGAColor(255, 255, 255);
	TGAImage m_renderOutput;
	int m_width;
	int m_height;
	std::vector<Light> m_lights;

	// Functions.
public:

	Renderer(int width, int height);
	void RenderWireframe(OBJFile& file);
	void RenderFile(OBJFile& file);
	void SaveRender(const char* fileName);
	void AddLight(Light& light);

private:

	void RenderLine(int x1, int y1, int x2, int y2);
	float Lighting(Vector3& a, Vector3& b, Vector3& c, Light& light);
	void RenderTriangle(Vector3& a, Vector3& b, Vector3& c, TGAColor& color);
};
