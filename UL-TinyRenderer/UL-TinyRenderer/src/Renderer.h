#pragma once

#include "TGAImage.h"
#include "OBJFile.h"

class Renderer
{

private:

	const TGAColor white = TGAColor(255, 255, 255);
	TGAImage m_renderOutput;
	int m_width;
	int m_height;

public:

	Renderer(int width, int height);
	void renderWireframe(OBJFile& file);
	void renderLine(int x1, int y1, int x2, int y2);
	void saveRender(const char* fileName);
};
