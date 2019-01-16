#include <iostream>
#include "Renderer.h"
#include "OBJFile.h"

int main()
{
	std::cout << "Hello World!" << std::endl;

	Renderer renderer(512, 512);

	OBJFile file("african_head.obj");

	renderer.renderWireframe(file);
	renderer.saveRender("Output.tga");

	std::cout << "Press any key to continue..." << std::endl;
	std::cin.get();
}
