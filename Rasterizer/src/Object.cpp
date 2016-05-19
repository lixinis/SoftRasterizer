#include "Object.h"
#include "ObjReader.h"

Object::Object()
{
    transform = new Transform();
}

Object::~Object()
{
    delete transform;
    delete mesh;
}

bool Object::LoadMesh(std::string path)
{
    mesh = ObjReader::ReadObj("box.obj");
    return (mesh != NULL);
}

