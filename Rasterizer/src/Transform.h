#pragma once

#include "Vector3.h"
#include "Matrix.h"

class Transform
{
public:
	Transform();
	~Transform();

    void Translate(Vector3 t);
    void Rotate(Vector3 r);
    void Scale(float s);
    void Scale(Vector3 s);
    
    Matrix ObjectToWorld();
private:
	Vector3 position;
	Vector3 eulerAngles;
	Vector3 scale;
    
    Matrix objectToWorld;
};

