#pragma once

#include "Vector3.h"
#include "Vector2.h"
#include "Color.h"

class Vertex
{
public:
	Vertex() {};
	Vertex(float x, float y, float z)
	{
		position = Vector3(x, y, z);
	}

	~Vertex(){};

	Vector3 position;
	Vector3 normal;
	Vector2 uv;
	Color color;
private:
};