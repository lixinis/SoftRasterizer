#pragma once

#include "Mesh.h"

class ObjReader
{
public:
	ObjReader();
	~ObjReader();

	Mesh* ReadObj(string filePath);
private:

};
