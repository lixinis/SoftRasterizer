#include <iostream>
#include <vector>
#include <algorithm>

#include "float.h"

#include "Canvas.h"
#include "Mesh.h"
#include "Matrix.h"
#include "ObjReader.h"

Canvas::Canvas()
{

}

Canvas::Canvas(int w, int h)
{
	frameBuffer = new uint32_t[w * h];
	zbuffer = new float[w * h];
	width = w;
	height = h;
}

void Canvas::Init()
{
    Object *box = new Object();
    if(box->LoadMesh("res/box.obj"))
    {
        box->transform->Translate(Vector3(0, -1, 0));
        box->transform->Scale(0.05f);
        objs.push_back(box);
    }
    Light *l = new Light();
    l->direction = Vector3(1, -1, 1);
    lights.push_back(l);
}

void Canvas::PutPixel(Vector3 v, Color color)
{
	int index = width * (int)v.y + (int)v.x;

	float depth = zbuffer[index];
	if (v.z > depth)
	{
		return;
	}

	zbuffer[index] = v.z;
	frameBuffer[index] = color.ToU32T();
}

void Canvas::DrawPoint(Vertex& v)
{
	if (v.position.x >= 0 && v.position.y >= 0 &&
		v.position.x < width && v.position.y < height)
	{
        v.color = v.color * std::max(0.0f, v.normal.Dot(Vector3(1,1,-1).Normalize()));
		PutPixel(v.position, v.color);
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
            Vertex v = Vertex(Vector3(x, y, 0), c);
			DrawPoint(v);
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
            Vertex v = Vertex(Vector3(x, y, 0), c);
            DrawPoint(v);
		}
	}
}

 
void Canvas::DrawScanline(Vertex &v1, Vertex &v2)
{
	int x1 = v1.position.x;
	int x2 = v2.position.x;
	int sign = x2 > x1 ? 1 : -1;
	float factor = 0;

	for (int x = x1, i = 0; i < (x2 - x1) * sign + 1; i++, x += sign) {
		if (x2 != x1) {
			factor = (float)(x - x1) / (x2 - x1);
		}
		auto v = v1.Interpolate(v2, factor);

		DrawPoint(v);
	}
}

void Canvas::DrawTriangle(Vector3& v1, Vector3& v2, Vector3& v3,
                          Vector3& normal1, Vector3& normal2, Vector3& normal3,
                          Vector2& uv1, Vector2& uv2, Vector2& uv3)
{
    //DrawLine(v1, v2);
    //DrawLine(v2, v3);
    //DrawLine(v3, v1);
    
	// sort a b c by y, top to bottom
    ///*
    
    Vertex a, b, c;
    a.position = v1; a.normal = normal1; a.uv = uv1;
    b.position = v2; b.normal = normal2; b.uv = uv2;
    c.position = v3; c.normal = normal3; c.uv = uv3;
    
	if (a.position.y > b.position.y)
	{
		std::swap(a, b);
	}
	if (b.position.y > c.position.y) 
	{
		std::swap(b, c);
	}
	if (a.position.y > b.position.y) 
	{
		std::swap(a, b);
	}

	float middleFactor = (float)(b.position.y - a.position.y) / (c.position.y - a.position.y);
	Vertex middle = a.Interpolate(c, middleFactor);

	int startY = a.position.y;
	int endY = b.position.y;
	for (int y = startY; y <= endY; ++y) 
	{
		float factor = 0;
		if (endY != startY) 
		{
			factor = (float)(y - startY) / (endY - startY);
		}
		Vertex va = a.Interpolate(b, factor);
		Vertex vb = a.Interpolate(middle, factor);
		DrawScanline(va, vb);
	}
	startY = b.position.y;
	endY = c.position.y;
	for (int y = startY; y <= endY; ++y) 
	{
		float factor = 0;
		if (endY != startY) 
		{
			factor = (float)(y - startY) / (endY - startY);
		}
		Vertex va = b.Interpolate(c, factor);
		Vertex vb = middle.Interpolate(c, factor);
		DrawScanline(va, vb);
	}
	startY = b.position.y;
	endY = c.position.y;
	for (int y = startY; y <= endY; ++y) 
	{
		float factor = 0;
		if (endY != startY) 
		{
			factor = (float)(y - startY) / (endY - startY);
		}
		Vertex va = b.Interpolate(c, factor);
		Vertex vb = middle.Interpolate(c, factor);
		DrawScanline(va, vb);
	}
     //*/
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
				objs[0]->transform->Rotate(Vector3(2, 0, 0));
				break;
			case SDLK_DOWN:
				objs[0]->transform->Rotate(Vector3(-2, 0, 0));
				break;
			case SDLK_LEFT:
				objs[0]->transform->Rotate(Vector3(0, 2, 0));
				break;
			case SDLK_RIGHT:
				objs[0]->transform->Rotate(Vector3(0, -2, 0));
				break;
			default:
				break;
			}
			return false;
		}
	}
    return false;
}

void Canvas::DrawObject(Object *o)
{
    Mesh *mesh = o->mesh;
    Matrix world = o->transform->ObjectToWorld();
    
    Vector3 eye = Vector3(0, 0, -10);
    Vector3 lookAt = Vector3(0, 0, 0);
    Vector3 up = Vector3(0, 1, 0);
    Matrix viewMatrix = Matrix::LookAtLH(eye, lookAt, up);
    
    Matrix projMatrix = Matrix::PerspectiveFovLH(60.0f / 180.0f * PI , (float)width / height, 0.1, 2);
    
    Matrix transform = world * viewMatrix * projMatrix;
    
    for (int i = 0; i < mesh->triangles.size(); i+=3)
    {
        int index1 = mesh->triangles[i];
        int index2 = mesh->triangles[i + 1];
        int index3 = mesh->triangles[i + 2];
        
        Vector3 v1 = mesh->vertices[index1];
        Vector3 v2 = mesh->vertices[index2];
        Vector3 v3 = mesh->vertices[index3];
        
        v1 = Project(v1, transform);
        v2 = Project(v2, transform);
        v3 = Project(v3, transform);
        
        DrawTriangle(v1, v2, v3,
                     mesh->normals[index1], mesh->normals[index2], mesh->normals[index3],
                     mesh->uvs[index1], mesh->uvs[index2], mesh->uvs[index3]);
    }
}

void Canvas::Render()
{
	Clear(Color(0, 0, 0, 1));

    for (int i = 0; i < objs.size(); i++) {
        DrawObject(objs[i]);
    }
}

Vector3 Canvas::Project(Vector3& v, Matrix& transform)
{
	Vector3 pos = transform.Transform(v);
	float x = pos.x * width + width / 2.0f;
	float y = -pos.y * height + height / 2.0f;
	return v = Vector3(x, y, pos.z);
}

void Canvas::Clear(Color color)
{
	for (int i = 0; i < width * height; i++)
	{
		zbuffer[i] = FLT_MAX;
		frameBuffer[i] = color.ToU32T();
	}
}

void Canvas::Present()
{
	SDL_RenderPresent(mRenderer);
}