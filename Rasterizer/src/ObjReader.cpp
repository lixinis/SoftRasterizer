#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

#include "ObjReader.h"

Mesh* ObjReader::ReadObj(string path)
{
	Mesh* mesh = new Mesh();

	std::vector<Vector3> temp_vertices;
    std::vector<Vector3> temp_normals;
    std::vector<Vector2> temp_uvs;
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
			Vector3 v;

			std::istringstream s(str.substr(2));
			s >> v.x >> v.y >> v.z;
			temp_vertices.push_back(v);
		}
        else if(str.substr(0,2) == "vt")
        {
            Vector2 uv;
            std::istringstream s(str.substr(2));
            s >> uv.x >> uv.y;
            temp_uvs.push_back(uv);
        }
        else if(str.substr(0,2) == "vn")
        {
            Vector3 normal;
            std::istringstream s(str.substr(2));
            s >> normal.x >> normal.y >> normal.z;
            temp_normals.push_back(normal);
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

    for (int i = 0; i < vertexIndices.size(); i++)
    {
        mesh->triangles.push_back(i);
        mesh->vertices.push_back(temp_vertices[vertexIndices[i] - 1]);
        mesh->normals.push_back(temp_normals[normalIndices[i] - 1]);
        mesh->uvs.push_back(temp_uvs[uvIndices[i] - 1]);
    }
    
	return mesh;
}