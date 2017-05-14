// Game_SDL_Game_Development_Studying.cpp : Defines the entry point for the console application.
//

#include "libraries.h"
#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;
float m_fps;
float m_maxFPS = 60.0f;
float m_frameTime;

Game* g_game = 0;



int main(int argc, char* argv[])
{
	srand( time(NULL) );
	

	Uint32 frameStart, frameTime;
	if (Game::Instance()->init("Chapter 1", 100, 100, 640, 480, SDL_WINDOW_OPENGL)) 
	{
		while (Game::Instance()->running())   
		{
			Game::Instance()->run();
		}
	}
	else  { return -1; }

	Game::Instance()->clean();

	return 0;
}

