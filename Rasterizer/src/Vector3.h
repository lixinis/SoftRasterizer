#pragma once
class Vector3
{
public:
	Vector3();
	Vector3(float nx, float ny, float nz)
		:x(nx), y(ny), z(nz)
	{

	}

	Vector3& operator=(Vector3& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;
		return *this;
	}

	~Vector3();
public:
	float x;
	float y;
	float z;
};

