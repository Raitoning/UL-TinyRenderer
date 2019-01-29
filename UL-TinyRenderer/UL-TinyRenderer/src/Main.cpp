#include <iostream>
#include "Renderer.h"
#include "OBJFile.h"
#include "Light.h"

#define LOG(X) std::cout << X << std::endl

int main()
{
	std::cout << "Hello World!" << std::endl;

	Renderer renderer(512, 512);

	Light redLight;
	redLight.SetColor(1.0f, 0.0f, 0.0f);
	redLight.SetDirection(-0.25f, 0.0f, 1.0f);

	Light greenLight;
	greenLight.SetColor(0.0f, 1.0f, 0.0f);
	greenLight.SetDirection(0.0f, 0.0f, 1.0f);

	Light blueLight;
	blueLight.SetColor(0.0f, 0.0f, 1.0f);
	blueLight.SetDirection(0.25f, 0.0f, 1.0f);

	renderer.AddLight(redLight);
	renderer.AddLight(greenLight);
	renderer.AddLight(blueLight);

	OBJFile file("african_head.obj");

	renderer.RenderFile(file);
	// renderer.RenderWireframe(file);
	renderer.SaveRender("Output.tga");

	LOG("Press any key to continue...");

	std::cin.get();
}
