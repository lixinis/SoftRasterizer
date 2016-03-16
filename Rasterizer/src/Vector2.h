#pragma once
class Vector2
{
public:
	Vector2();
	Vector2(float nx, float ny)
		:x(nx), y(ny)
	{

	}

	void operator=(const Vector2& vec)
	{
		x = vec.x;
		y = vec.y;
	}

	~Vector2();
public:
	float x;
	float y;
};

