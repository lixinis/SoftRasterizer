#pragma once

#include <math.h>

class Vector3
{
public:
	Vector3();
	Vector3(float nx, float ny, float nz)
		:x(nx), y(ny), z(nz)
	{

	}

	float Length()
	{
		return sqrtf(x * x + y * y + z * z);
	}

	Vector3 Normalize()
	{
		float factor = 0;
		float length = Length();
		if (length > 0)
		{
			factor = 1 / length;
		}
		return Vector3(x * factor, y * factor, z * factor);
	}

	Vector3 operator+(const Vector3& vec) const
	{
		return Vector3(x + vec.x, y + vec.y, z + vec.z);
	}

	void operator+=(const Vector3& vec)
	{
		x += vec.x; y += vec.y; z += vec.z;
	}

	Vector3 operator-(const Vector3& vec) const
	{
		return Vector3(x - vec.x, y - vec.y, z - vec.z);
	}

	Vector3 Cross(const Vector3& vec) const
	{
		float nx = y * vec.z - z * vec.y;
		float ny = z * vec.x - x * vec.z;
		float nz = x * vec.y - y * vec.x;
		return Vector3(nx, ny, nz);
	}

	float Dot(const Vector3& vec)
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}

	Vector3 operator=(const Vector3& vec)
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

