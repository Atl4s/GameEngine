#include "stdafx.h"
#include "Window.h"
#include "Errors.h"

Window::Window()
{
}


Window::~Window()
{
}

int Window::create(std::string title, int xPosition, int yPosition, int width, int height, Uint32 flags)
{

	m_width = width;
	m_height = height;
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	_pWindow = SDL_CreateWindow(title.c_str(), xPosition, yPosition,
		width, height, flags);

	if (_pWindow == nullptr) // window init success
	{
		fatalError("can't create window");
	}

	SDL_GLContext m_glContext = SDL_GL_CreateContext(_pWindow);
	_pRenderer = SDL_CreateRenderer(_pWindow, -1, 0);
	if (!_pRenderer) fatalError("can't create renderer");
	if (!m_glContext) fatalError("can't create glContext");
	
	if (glewInit() == GLEW_OK)
	{
		SDL_SetRenderDrawColor(_pRenderer,
			255, 255, 255, 255);

		std::printf("***    OpenGL version: %s    ***\n", glGetString(GL_VERSION));
		std::printf("***    GLSL version: %s    ***\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

			//set VSYNC
		SDL_GL_SetSwapInterval(1);

		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	}
	
	return 1;
}