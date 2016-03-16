#pragma once

#include "Mesh.h"

class ObjReader
{
public:
	ObjReader();
	~ObjReader();

	Mesh* ReadObj(char* filePath);
private:

};
