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
				std::vector<std::string> vertex = explode(line, ' ');

				float x = std::atof(vertex[1].c_str());
				float y = std::atof(vertex[2].c_str());
				float z = std::atof(vertex[3].c_str());

				vertices.push_back(Vector3(x, y, z));
			}

			if (line.find("f ", 0) == 0)
			{
				std::vector<std::string> vertex;
				std::vector<std::string> face = explode(line, ' ');

				float x = std::atof(explode(face[1], '/')[0].c_str());
				float y = std::atof(explode(face[2], '/')[0].c_str());
				float z = std::atof(explode(face[3], '/')[0].c_str());

				faces.push_back(Vector3(x, y, z));
			}
		}
		file.close();
	}
}

const std::vector<Vector3>& OBJFile::getVertices()
{
	return vertices;
}

const std::vector<Vector3>& OBJFile::getFaces()
{
	return faces;
}


OBJFile::~OBJFile()
{
}

// Function to split a string into multiple strings.
// Code from Cplusplus.com
// http://www.cplusplus.com/articles/2wA0RXSz/
const std::vector<std::string> OBJFile::explode(const std::string& s, const char& c)
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
