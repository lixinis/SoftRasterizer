#pragma once

#include <SDL.h>

#include "Mesh.h"
#include "Matrix.h"
#include "Vertex.h"

#pragma once
class Canvas
{
public:
	Canvas();
	Canvas(int w, int h);

	virtual ~Canvas()
	{
		delete mesh;
		delete[] frameBuffer;
		delete[] zbuffer;
	};

	bool HandleInput();

	void Render();
	void Clear(Color color);

	void Project(Vertex& v, Matrix& transform);

	void PutPixel(Vector3 pos, Color color);
	void DrawPoint(Vertex& vert);
	void DrawScanline(Vertex &v0, Vertex &v1);
	void DrawLine(Vertex& v1, Vertex& v2);
	void DrawTriangle(Vertex& v1, Vertex& v2, Vertex&v3);

	void Present();
public:
	uint32_t *frameBuffer;
	float *zbuffer;
private:
	int width;
	int height;
	SDL_Renderer *mRenderer;

	// for test input
	Vector3 rotation;

	Mesh *mesh;
};

