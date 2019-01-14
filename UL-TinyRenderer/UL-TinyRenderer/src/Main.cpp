#include <iostream>
#include "Renderer.h"

int main()
{
	std::cout << "Hello World!" << std::endl;

	Renderer renderer(256, 256);
	renderer.renderLine(0, 0, 255, 255);
	renderer.renderLine(0, 255, 256, 0);
	renderer.saveRender("Output.tga");

	std::cin.get();
}
