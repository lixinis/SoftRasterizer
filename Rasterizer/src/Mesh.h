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
	vector<Vertex> vertices;
	vector<int> indices;
};