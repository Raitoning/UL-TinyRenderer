#pragma once
#include <vector>
#include <string>
#include "Vector3.h"

class OBJFile
{

private:
	std::vector<Vector3> m_vertices;

	// TODO: Find a better way to store infos about faces.
	std::vector<Vector3> m_faces;
	std::vector<Vector3> m_textels;
	std::vector<Vector3> m_textureCoordinates;

public:
	OBJFile(const char * fileName);

	const std::vector<Vector3>& GetVertices();
	const std::vector<Vector3>& GetFaces();
	const std::vector<Vector3>& GetTextels();
	const std::vector<Vector3>& GetTextureCoordinates();

private:
	const std::vector<std::string> Explode(const std::string& s, const char& c);
};
