#pragma once

#include "Vector3.h"
#include "Vector2.h"
#include "Color.h"

class Vertex
{
public:
	Vertex()
    {
        position = Vector3::Zero();
        color = Color(1,1,1,1);
    }
    
	Vertex(float x, float y, float z)
	{
		position = Vector3(x, y, z);
        color = Color(1, 1, 1, 1);
	}

	Vertex(Vector3 pos, Color c)
	{
		position = pos;
		color = c;
	}

	~Vertex(){}

	Vertex Interpolate(const Vertex &vertex, float factor) const {
        Vertex v;
		v.position = position.Interpolate(vertex.position, factor);
		v.color = color.Interpolate(vertex.color, factor);
        v.normal = normal.Interpolate(vertex.normal, factor);
        
        return v;
	}

	Vector3 position;
	Vector3 normal;
	Vector2 uv;
	Color color;
private:
};