#pragma once
#include <vector>
#include <string>
#include "Vector3.h"

class OBJFile
{

private:
	std::vector<Vector3> vertices;

	// TODO: Find a better way to store infos about faces.
	std::vector<Vector3> faces;

public:
	OBJFile(const char * fileName);
	~OBJFile();

	const std::vector<Vector3>& getVertices();
	const std::vector<Vector3>& getFaces();

private:
	const std::vector<std::string> explode(const std::string& s, const char& c);
};
