#pragma once

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
public:
	float m[4][4];
};