#pragma once

class Color
{
public:
	Color() {};
	Color(float nr, float ng, float nb, float na) : r(nr), g(ng), b(nb), a(na) {};

	~Color() {};

public:
	float r;
	float g;
	float b;
	float a;
};