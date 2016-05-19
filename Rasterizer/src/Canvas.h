#pragma once

#include <vector>
#include <SDL.h>

#include "Mesh.h"
#include "Matrix.h"
#include "Vertex.h"
#include "Object.h"
#include "Light.h"

#pragma once
class Canvas
{
public:
	Canvas();
	Canvas(int w, int h);

	virtual ~Canvas()
	{
		//delete mesh;
		delete[] frameBuffer;
		delete[] zbuffer;
	};

	bool HandleInput();

    void Init();
    
	void Render();
	void Clear(Color color);

	Vector3 Project(Vector3& v, Matrix& transform);

	void PutPixel(Vector3 pos, Color color);
	void DrawPoint(Vertex& vert);
	void DrawScanline(Vertex &v0, Vertex &v1);
	void DrawLine(Vertex& v1, Vertex& v2);
    
    void DrawTriangle(Vector3& v1, Vector3& v2, Vector3& v3,
                      Vector3& normal1, Vector3& normal2, Vector3& normal3,
                      Vector2& uv1, Vector2& uv2, Vector2& uv3);

	void Present();
public:
	uint32_t *frameBuffer;
	float *zbuffer;
private:
    void DrawObject(Object *o);
    
	int width;
	int height;
	SDL_Renderer *mRenderer;

    vector<Object*> objs;
    vector<Light*> lights;
    
	//Mesh *mesh;
};

