#pragma once

#include <iostream>
#include "Mesh.h"
#include "Transform.h"

class Object
{
public:
    Object();
    ~Object();
    
    bool LoadMesh(std::string path);
public:
    Mesh *mesh;
    Transform *transform;
private:
    
};