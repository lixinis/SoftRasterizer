#pragma once
#include "Canvas.h"

class Window
{
public:
	Window();
	~Window();

	int Init();
	void Input();
	void Update();
private:
	Canvas *mCanvas;
	bool bQuit = false;
};

