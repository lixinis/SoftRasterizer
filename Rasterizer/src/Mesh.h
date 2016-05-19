#pragma once

#include <vector>
#include "Vertex.h"

using namespace std;

class Mesh
{
public:
	Mesh() {};
	~Mesh() {};


public:
	vector<Vector3> vertices;
    vector<Vector3> normals;
    vector<Vector2> uvs;
	vector<int> triangles;
};