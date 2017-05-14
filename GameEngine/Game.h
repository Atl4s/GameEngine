#pragma once

#include "stdafx.h"
#include <iostream>
#include "math.h"
#include <string>
#include <map>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <ctime>
#include <random>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "ResourceManager.h"
#include "Player.h"
#include "Enemy.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"
#include "ParticleEngine.h"
#include "GLTexture.h"
#include "GLSLProgram.h"
#include "Sprite.h"
#include "Camera2D.h"
#include "SpriteBatch.h"
#include "Window.h"
#include <vector>
#include <string>

class Game
{
protected:
	Game() :m_time(0.0f) {};
	~Game(){};
	static Game* s_pInstance;
public:
	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}

	static bool DeleteInstance()
	{
		if (s_pInstance)
		{
			delete s_pInstance;
			s_pInstance = 0;
			return true;
		}
		return false;
	}

	std::vector<SDLGameObject*> m_gameObjects;

	void run();
	void render();
	void update();
	void clean();
	bool init(const char* title, int xpos, int ypos, int width, int height, Uint32 flags);
	bool running() { return m_bRunning; }
	SDL_Renderer* getRenderer() const { return m_pRenderer; }
	Window* getWindow() { return _pWindows.back(); }

	GameStateMachine* getStateMachine(){ return m_pGameStateMachine;  }


private:
	GameStateMachine* m_pGameStateMachine;
	std::vector<Window*> _pWindows;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;
	int m_currentFrame;
	SpriteBatch m_spriteBatch;

	GLSLProgram m_colorProgram;
	void initShaders();

	float m_time;
};