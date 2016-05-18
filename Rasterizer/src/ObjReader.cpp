#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

#include "ObjReader.h"

ObjReader::ObjReader()
{
}

ObjReader::~ObjReader()
{
}

Mesh* ObjReader::ReadObj(string path)
{
	Mesh* mesh = new Mesh();

	std::vector<Vertex> vertices;
	std::vector<int> vertexIndices;
	std::vector<int> uvIndices;
	std::vector<int> normalIndices;

	ifstream file(path.c_str(), ios::in);
	if (!file)
	{
		std::cout << "Read File Failed!";
		return NULL;
	}

	string str;
	while (std::getline(file, str))
	{
		if (str.substr(0, 2) == "v ")
		{
			Vertex v;

			std::istringstream s(str.substr(2));
			s >> v.position.x >> v.position.y >> v.position.z;
			v.color = Color(255, 255, 255, 255);
			vertices.push_back(v);
		}
		else if (str.substr(0,2) == "f ")
		{
			string vertex1, vertex2, vertex3;
			int vertexIndex[3], uvIndex[3], normalIndex[3];

			std::replace(str.begin(), str.end(), '/', ' ');
			std::istringstream s(str.substr(2));
			s >> vertexIndex[0] >> uvIndex[0] >> normalIndex[0] >> vertexIndex[1] >> uvIndex[1] >> normalIndex[1] >> vertexIndex[2] >> uvIndex[2] >> normalIndex[2];

			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	cout << "out!";

	mesh->vertices = vertices;
	mesh->indices = vertexIndices;

	return mesh;
}