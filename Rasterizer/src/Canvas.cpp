#include <iostream>
#include <vector>

#include "Canvas.h"
#include "Mesh.h"
#include "Matrix.h"

Canvas::Canvas()
{
}

void Canvas::DrawPoint(Vertex& v)
{
	if (v.position.x >= 0 && v.position.y >= 0 &&
		v.position.x < width && v.position.y < height)
	{
		frameBuffer[width * (int)v.position.y + (int)v.position.x] = v.color.ToU32T();
	}
}

/// use bresemham line drawing algrithom
void Canvas::DrawLine(Vertex& v1, Vertex& v2)
{
	int x1 = (int)v1.position.x;
	int y1 = (int)v1.position.y;
	int x2 = (int)v2.position.x;
	int y2 = (int)v2.position.y;

	int dx = x2 - x1;
	int dy = y2 - y1;

	if (abs(dx) > abs(dy)) {
		int sign = x2 - x1 > 0 ? 1 : -1;
		float ratio = 0;
		if (dx != 0) {
			ratio = (float)dy / dx;
		}

		for (int x = x1; x != x2; x += sign) {
			int y = y1 + (x - x1) * ratio;
			Color c = v1.color + ((v2.color - v1.color) * ((float)(x - x1) / (x2 - x1)));
			DrawPoint(Vertex(Vector3(x, y, 0), c));
		}
	}
	else {
		int sign = y2 - y1 > 0 ? 1 : -1;
		float ratio = 0;
		if (dy != 0) {
			ratio = (float)dx / dy;
		}

		for (int y = y1; y != y2; y += sign) {
			int x = x1 + (y - y1) * ratio;
			Color c = v1.color + ((v2.color - v1.color) * ((float)(y - y1) / (y2 - y1)));
			DrawPoint(Vertex(Vector3(x, y, 0), c));
		}
	}
}

void Canvas::DrawTriangle(Vertex& v1, Vertex& v2, Vertex& v3)
{
	DrawLine(v1, v2);
	DrawLine(v2, v3);
	DrawLine(v3, v1);
}

bool Canvas::HandleInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)){
		if (e.type == SDL_QUIT){
			return true;
		}
		else if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				return true;
				break;
			case SDLK_UP:
				rotation += Vector3(1, 0, 0);
				break;
			case SDLK_DOWN:
				rotation += Vector3(-1, 0, 0);
				break;
			case SDLK_LEFT:
				rotation += Vector3(0, 1, 0);
				break;
			case SDLK_RIGHT:
				rotation += Vector3(0, -1, 0);
				break;
			default:
				break;
			}
		}
	}
}

void Canvas::Render()
{
	Clear(Color(100, 0, 0, 255));

	Mesh* mesh = new Mesh();

	std::vector<Vertex> vertices(8);
	vertices[0] = Vertex(-1.0f,-1.0f, -1.0f);
	vertices[0].color = Color(255, 255, 255, 255);

	vertices[1] = Vertex(-1.0f, 1.0f, -1.0f);
	vertices[1].color = Color(255, 255, 255, 255);

	vertices[2] = Vertex(1.0f, 1.0f, -1.0f);
	vertices[2].color = Color(255, 255, 255, 255);

	vertices[3] = Vertex(1.0f, -1.0f, -1.0f);
	vertices[3].color = Color(255, 255, 255, 255);

	vertices[4] = Vertex(-1.0f, -1.0f, 1.0f);
	vertices[4].color = Color(255, 255, 255, 255);

	vertices[5] = Vertex(-1.0f, 1.0f, 1.0f);
	vertices[5].color = Color(255, 255, 255, 255);

	vertices[6] = Vertex(1.0f, 1.0f, 1.0f);
	vertices[6].color = Color(255, 255, 255, 255);

	vertices[7] = Vertex(1.0f, -1.0f, 1.0f);
	vertices[7].color = Color(255, 255, 255, 255);

	mesh->vertices = vertices;

	std::vector<int> indices(36);
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	indices[6] = 4; indices[7] = 6; indices[8] = 5;
	indices[9] = 4; indices[10] = 7; indices[11] = 6;

	indices[12] = 4; indices[13] = 5; indices[14] = 1;
	indices[15] = 4; indices[16] = 1; indices[17] = 0;

	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;

	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;

	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;

	mesh->indices = indices;

	Matrix translateMatrix = Matrix::Translate(Vector3(0, 0, 0));
	Matrix rotateMatrix = Matrix::Rotate(rotation);
	Matrix scaleMatrix = Matrix::Scale(Vector3(1, 1, 1));
	Matrix world = scaleMatrix * rotateMatrix * translateMatrix;

	Vector3 eye = Vector3(0, 0, -10);
	Vector3 lookAt = Vector3(0, 0, 0);
	Vector3 up = Vector3(0, 1, 0);
	Matrix viewMatrix = Matrix::LookAtLH(eye, lookAt, up);

	Matrix projMatrix = Matrix::PerspectiveFovLH(60.0f / 180.0f * PI , (float)width / height, 0.1, 2);

	Matrix transform = world * viewMatrix * projMatrix;

	for (int i = 0; i < mesh->vertices.size(); i++)
	{
		Vertex v1 = mesh->vertices[mesh->indices[i * 3]];
		Vertex v2 = mesh->vertices[mesh->indices[i * 3 + 1]];
		Vertex v3 = mesh->vertices[mesh->indices[i * 3 + 2]];

		Project(v1, transform);
		Project(v2, transform);
		Project(v3, transform);

		DrawTriangle(v1, v2, v3);
	}

	delete mesh;
}

void Canvas::Project(Vertex& v, Matrix& transform)
{
	Vector3 pos = transform.Transform(v.position);
	float x = pos.x * width + width / 2.0f;
	float y = -pos.y * height + height / 2.0f;
	v.position = Vector3(x, y, 0);
}

void Canvas::Clear(Color color)
{
	for (int i = 0; i < width * height; i++)
	{
		frameBuffer[i] = color.ToU32T();
	}
}

void Canvas::Present()
{
	SDL_RenderPresent(mRenderer);
}