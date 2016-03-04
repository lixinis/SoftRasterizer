#include <iostream>
#include "Canvas.h"


Canvas::Canvas()
{
}


Canvas::~Canvas()
{
}

void Canvas::DrawPoint(Vertex& v)
{
	SDL_SetRenderDrawColor(mRenderer, v.color.r, v.color.g, v.color.b, v.color.a);
	SDL_RenderDrawPoint(mRenderer, v.position.x, v.position.y);
}

void Canvas::DrawLine(Vertex& v1, Vertex& v2)
{
	Vector3 pos1 = v1.position;
	Vector3 pos2 = v2.position;

	float slope = (pos2.y - pos1.y) / (pos2.x - pos1.x);
	float minX, maxX;
	if (pos1.x < pos2.x)
	{
		minX = pos1.x;
		maxX = pos2.x;
	}
	else
	{
		minX = pos2.x;
		maxX = pos1.x;
	}
	for (float x = minX; x < maxX; x++)
	{
		float y = pos1.y + slope * (x - pos1.x);
		SDL_RenderDrawPoint(mRenderer, x, y);
	}
}

void Canvas::Clear(Color color)
{
	SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(mRenderer);
}

void Canvas::Present()
{
	SDL_RenderPresent(mRenderer);
}