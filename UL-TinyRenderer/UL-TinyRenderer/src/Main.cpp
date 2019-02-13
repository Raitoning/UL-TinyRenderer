#include <iostream>
#include "Renderer.h"
#include "OBJFile.h"
#include "Light.h"

#define LOG(X) std::cout << X << std::endl

int main()
{
	std::cout << "Hello World!" << std::endl;

	Renderer renderer(1024, 1024);

	Light whiteLight;
	whiteLight.SetColor(1.0f, 1.0f, 1.0f);
	whiteLight.SetDirection(0.0f, 0.0f, -1.0f);

	Light blueLight;
	blueLight.SetColor(0.0f, 0.0f, 1.0f);
	blueLight.SetDirection(1.0f, 0.0f, -1.0f);

	Light redLight;
	redLight.SetColor(1.0f, 0.0f, 0.0f);
	redLight.SetDirection(-1.0f, 0.0f, -1.0f);

	renderer.AddLight(whiteLight);
	renderer.AddLight(blueLight);
	renderer.AddLight(redLight);
	renderer.SetAmbientLighting(0.125f, 0.125f, 0.125f);

	OBJFile file("african_head.obj");

	TGAImage diffuseTexture;
	diffuseTexture.read_tga_file("african_head_diffuse.tga");

	renderer.SetDiffuseTexture(diffuseTexture);

	renderer.RenderFile(file);
	renderer.SaveRender("Output.tga");

	LOG("Press any key to continue...");

	std::cin.get();
}
