#pragma once

#include "Vector3.h"

#define PI 3.1415926

class Matrix
{
public:
	Matrix() {};
	Matrix(float p[4][4])
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m[i][j] = p[i][j];
			}
		}
	}

	~Matrix() {};

	float At(int r, int c) const
	{
		return m[r][c];
	};

	Matrix operator*(const Matrix &matrix) const
	{
		float r[4][4] = { 0 };
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				r[i][j] = m[i][0] * matrix.At(0, j) + m[i][1] * matrix.At(1, j) + m[i][2] * matrix.At(2, j) + m[i][3] * matrix.At(3, j);
			}
		}
		return Matrix(r);
	};

	Vector3 Transform(const Vector3& v)
	{
		float x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0];
		float y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1];
		float z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2];
		float w = v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + m[3][3];
		return Vector3(x/w, y/w, z/w);
	};

	static Matrix RotateX(float angle)
	{
		angle = angle / 180 * PI;
		float cos = cosf(angle);
		float sin = sinf(angle);
		float p[4][4] =
		{
			{ 1, 0, 0, 0 },
			{ 0, cos, sin, 0 },
			{ 0, -sin, cos, 0 },
			{ 0, 0, 0, 1 }
		};
		return Matrix(p);
	};

	static Matrix RotateY(float angle)
	{
		angle = angle / 180 * PI;
		float cos = cosf(angle);
		float sin = sinf(angle);
		float p[4][4] =
		{
			{ cos, 0, -sin, 0 },
			{ 0, 1, 0, 0 },
			{ sin, 0, cos, 0 },
			{ 0, 0, 0, 1 }
		};
		return Matrix(p);
	};
	
	static Matrix RotateZ(float angle)
	{
		angle = angle / 180 * PI;
		float cos = cosf(angle);
		float sin = sinf(angle);
		float p[4][4] =
		{
			{ cos, sin, 0, 0 },
			{ -sin, cos, 0, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 1 }
		};
		return Matrix(p);
	};

	static Matrix Rotate(const Vector3 &v)
	{
		Matrix rotateX = Matrix::RotateX(v.x);
		Matrix rotateY = Matrix::RotateY(v.y);
		Matrix rotateZ = Matrix::RotateZ(v.z);
		return rotateZ * rotateY * rotateX;
	};

	static Matrix Translate(const Vector3& t)
	{
		float p[4][4] = 
		{
			{ 1, 0, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 1, 0 },
			{ t.x, t.y, t.z, 1}
		};
		return Matrix(p);
	};

	static Matrix Scale(const Vector3& s)
	{
		float p[4][4] =
		{
			{ s.x, 0, 0, 0 },
			{ 0, s.y, 0, 0 },
			{ 0, 0, s.z, 0 },
			{ 0, 0, 0, 1 }
		};
		return Matrix(p);
	};

	static Matrix LookAtLH(const Vector3& eye, const Vector3& at, const Vector3& up)
	{
		Vector3 zaxis = (at - eye).Normalize();
		Vector3 xaxis = up.Cross(zaxis).Normalize();
		Vector3 yaxis = zaxis.Cross(xaxis).Normalize();

		float eyeX = -xaxis.Dot(eye);
		float eyeY = -yaxis.Dot(eye);
		float eyeZ = -zaxis.Dot(eye);

		float p[4][4] =
		{
			{ xaxis.x, yaxis.x, zaxis.x, 0 },
			{ xaxis.y, yaxis.y, zaxis.y, 0 },
			{ xaxis.z, yaxis.z, zaxis.z, 0 },
			{ eyeX, eyeY, eyeZ, 1 }
		};
		return Matrix(p);
	};

	static Matrix PerspectiveFovLH(float fov, float aspect, float zn, float zf)
	{
		float yScale = 1 / tan(fov / 2);
		float xScale = yScale / aspect;

		float p[4][4] = 
		{
			{ xScale, 0, 0, 0 },
			{ 0, yScale, 0 ,0 },
			{ 0, 0, zf / (zf - zn), 1 },
			{ 0, 0, -zn * zf / (zf - zn), 0 }
		};
		return Matrix(p);
	};

public:
	float m[4][4];
};