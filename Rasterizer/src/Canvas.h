#include <SDL.h>
#include "Color.h"
#include "Vertex.h"

#pragma once
class Canvas
{
public:
	Canvas();
	Canvas(SDL_Renderer *renderer):
		mRenderer(renderer)
	{

	};

	virtual ~Canvas();

	void Clear(Color color);

	void DrawPoint(Vertex& vert);
	void DrawLine(Vertex& v1, Vertex& v2);

	void Present();
private:
	SDL_Renderer *mRenderer;
};

