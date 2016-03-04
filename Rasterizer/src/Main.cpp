#include <iostream>
#include "Window.h"

int main(int, char**)
{
	Window *win = new Window();

	if (win->Init() != 0)
	{
		std::cout << "Window Init failed!" << std::endl;
		return 1;
	}

	return 0;
}