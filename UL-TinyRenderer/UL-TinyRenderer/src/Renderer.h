#pragma once

#include <algorithm>
#include "TGAImage.h"
#include "OBJFile.h"
#include "Light.h"
#include "Matrix.h"

class Renderer
{
	// Members.
private:

	const TGAColor white = TGAColor(255, 255, 255);
	TGAImage m_renderOutput;
	int m_width;
	int m_height;
	std::vector<Light> m_lights;
	std::vector<float> m_zBuffer;
	Vector3 m_ambientLighting;
	TGAImage m_diffuseTexture;
	Vector3 m_camera;

	// Functions.
public:

	Renderer(int width, int height);
	void RenderWireframe(OBJFile& file);
	void RenderFile(OBJFile& file);
	void SaveRender(const char* fileName);
	void AddLight(Light& light);
	void SetAmbientLighting(float r, float g, float b);
	void SetDiffuseTexture(TGAImage texture);
	void SetCamera(float x, float y, float z);

private:

	void RenderLine(int x1, int y1, int x2, int y2);
	float Lighting(Vector3& a, Vector3& b, Vector3& c, Light& light);
	Vector3 BarycentricCoordinates(Vector3& a, Vector3& b, Vector3& c, Vector3& p);
	void RenderTriangle(Vector3& a, Vector3& b, Vector3& c, Vector3& u, Vector3& v, Vector3& w, Vector3& color);
};
