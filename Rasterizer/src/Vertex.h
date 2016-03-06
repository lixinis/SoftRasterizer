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

	Vertex(Vector3 pos, Color c)
	{
		position = pos;
		color = c;
	}

	~Vertex(){};

	Vector3 position;
	Color color;
private:
};