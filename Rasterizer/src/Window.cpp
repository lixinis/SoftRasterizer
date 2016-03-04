#include <iostream>
#include <SDL.h>

#include "Window.h"
#include "Canvas.h"
#include "Matrix.h"

Window::Window()
{
}


Window::~Window()
{
}

int Window::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init error:" << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Rasterizer", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == nullptr)
	{
		std::cout << "SDL_CreateWindow Error:" << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr){
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	mCanvas = new Canvas(ren);

	bQuit = false;

	while (!bQuit){
		Input();
		Update();
	}

	SDL_Quit();
	return 0;
}

void Window::Input()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)){
		if (e.type == SDL_QUIT){
			bQuit = true;
		}
		else if (e.type == SDL_KEYDOWN)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				bQuit = true;
				break;
			default:
				break;
			}
		}
	}
}

void Window::Update()
{
	mCanvas->Clear(Color(100, 0, 0, 255));
	Vertex v;
	v.position = Vector3(100, 100, 0);
	v.color = Color(255, 255, 255, 255);
	mCanvas->DrawPoint(v);

	float m[4][4] =
	{
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	};

	Matrix matrix(m);

	mCanvas->Present();
}