#include <SDL.h>
#include "Color.h"
#include "Matrix.h"
#include "Vertex.h"

#pragma once
class Canvas
{
public:
	Canvas();
	Canvas(int w, int h)
	{
		frameBuffer = new uint32_t[w * h];
		zbuffer = new float[w * h];
		width = w;
		height = h;
	};

	virtual ~Canvas()
	{
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
};

