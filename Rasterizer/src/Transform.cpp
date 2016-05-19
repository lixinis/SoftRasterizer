#include "Transform.h"


Transform::Transform()
{
    position = Vector3::Zero();
    eulerAngles = Vector3::Zero();
    scale = Vector3::One();
}


Transform::~Transform()
{
    
}

void Transform::Translate(Vector3 t)
{
    this->position = this->position + t;
}

void Transform::Rotate(Vector3 r)
{
    this->eulerAngles = this->eulerAngles + r;
}

void Transform::Scale(float s)
{
    this->scale = this->scale * s;
}

Matrix Transform::ObjectToWorld()
{
    Matrix translateMatrix = Matrix::Translate(position);
    Matrix rotateMatrix = Matrix::Rotate(eulerAngles);
    Matrix scaleMatrix = Matrix::Scale(scale);
    return scaleMatrix * rotateMatrix * translateMatrix;
}