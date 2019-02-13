#include "OBJFile.h"

#include <fstream>
#include <iostream>

OBJFile::OBJFile(const char* fileName)
{
	std::string line;

	std::ifstream file;
	file.open(fileName);


	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			if (line.find("v ", 0) == 0)
			{
				std::vector<std::string> vertex = Explode(line, ' ');

				float x = std::atof(vertex[1].c_str());
				float y = std::atof(vertex[2].c_str());
				float z = std::atof(vertex[3].c_str());

				m_vertices.push_back(Vector3(x, y, z));
			}

			if (line.find("vt  ", 0) == 0)
			{
				std::vector<std::string> textureCoordinates = Explode(line, ' ');

				float x = std::atof(textureCoordinates[1].c_str());
				float y = std::atof(textureCoordinates[2].c_str());
				float z = std::atof(textureCoordinates[3].c_str());

				m_textureCoordinates.push_back(Vector3(x, y, z));
			}

			if (line.find("f ", 0) == 0)
			{
				std::vector<std::string> face = Explode(line, ' ');

				float x = std::atof(Explode(face[1], '/')[0].c_str());
				float y = std::atof(Explode(face[2], '/')[0].c_str());
				float z = std::atof(Explode(face[3], '/')[0].c_str());

				float u = std::atof(Explode(face[1], '/')[1].c_str());
				float v = std::atof(Explode(face[2], '/')[1].c_str());
				float w = std::atof(Explode(face[3], '/')[1].c_str());

				m_faces.push_back(Vector3(x, y, z));
				m_textels.push_back(Vector3(u, v, w));
			}
		}
		file.close();
	}
}

const std::vector<Vector3>& OBJFile::GetVertices()
{
	return m_vertices;
}

const std::vector<Vector3>& OBJFile::GetFaces()
{
	return m_faces;
}

const std::vector<Vector3>& OBJFile::GetTextels()
{
	return m_textels;
}

const std::vector<Vector3>& OBJFile::GetTextureCoordinates()
{
	return m_textureCoordinates;
}

// Function to split a string into multiple strings.
// Code from Cplusplus.com
// http://www.cplusplus.com/articles/2wA0RXSz/
const std::vector<std::string> OBJFile::Explode(const std::string& s, const char& c)
{
	std::string buff{ "" };
	std::vector<std::string> v;

	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);

	return v;
}
