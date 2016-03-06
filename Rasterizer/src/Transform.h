#pragma once

#include "Vector3.h"

class Transform
{
public:
	Transform();
	~Transform();

public:
	Vector3 position;
	Vector3 eulerAngles;
	Vector3 scale;
};

