#include <iostream>
#include <vector>
#include <SDL.h>

#include "Window.h"
#include "Canvas.h"
#include "Matrix.h"
#include "Mesh.h"

Window::Window()
{
}


Window::~Window()
{
}

int Window::Init()
{
	int width = 640;
	int height = 480;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init error:" << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Rasterizer", 100, 100, width, height, SDL_WINDOW_SHOWN);
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

	SDL_Texture *texture = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	if (texture == NULL) {
		SDL_Quit();
		fprintf(stderr, "CreateTexture failed\n");
	}

	SDL_Rect *rect = new SDL_Rect();
	rect->x = 0;
	rect->y = 0;
	rect->w = width;
	rect->h = height;

	void *pixels;

	mCanvas = new Canvas(width, height);

	bQuit = false;

	while (!bQuit){
		bQuit = mCanvas->HandleInput();

		mCanvas->Render();

		SDL_UpdateTexture(texture, NULL, mCanvas->frameBuffer, 640 * sizeof(Uint32));

		SDL_RenderClear(ren);
		SDL_RenderCopy(ren, texture, NULL, NULL);
		SDL_RenderPresent(ren);
	}

	SDL_Quit();
	return 0;
}
