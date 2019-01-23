#pragma once

#include "TGAImage.h"
#include "OBJFile.h"

class Renderer
{
	// Members.
private:

	const TGAColor white = TGAColor(255, 255, 255);
	TGAImage m_renderOutput;
	int m_width;
	int m_height;


	// Functions.
public:

	Renderer(int width, int height);
	void renderWireframe(OBJFile& file);
	void renderFile(OBJFile& file);
	void saveRender(const char* fileName);

private:

	void renderLine(int x1, int y1, int x2, int y2);
	void renderTriangle(Vector3 a, Vector3 b, Vector3 c, TGAColor color);
};
