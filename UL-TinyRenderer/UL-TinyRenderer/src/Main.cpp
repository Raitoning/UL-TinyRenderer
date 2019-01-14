#include <iostream>
#include "Renderer.h"

int main()
{
	std::cout << "Hello World!" << std::endl;

	Renderer renderer(256, 256);
	renderer.renderLine(0, 0, 255, 255);
	renderer.renderLine(256, 0, 0, 255);
	renderer.renderLine(0, 255, 128, 0);
	renderer.renderLine(128, 0, 255, 255);
	renderer.renderLine(0, 0, 128, 255);
	renderer.renderLine(128, 255, 255, 0);
	renderer.saveRender("Output.tga");

	std::cin.get();
}
