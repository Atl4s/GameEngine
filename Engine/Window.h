#pragma once
#include "libraries.h"

enum flags {
	INVISIBLE = 0x1,
	FULLSCREEN = 0x2,
	BORDERLESS = 0x4
};

class Window
{
public:
	Window();
	~Window();

	int create(std::string title, int xPosition, int yPosition, int width, int height, Uint32 flags);

	void swapBuffer() {
		SDL_GL_SwapWindow(_pWindow);
	}

	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

	SDL_Window* getWindow() { return _pWindow; }
	SDL_Renderer* getRenderer() { return _pRenderer; }

private:
	SDL_Window* _pWindow;
	SDL_Renderer* _pRenderer;
	int m_width, m_height;
};

