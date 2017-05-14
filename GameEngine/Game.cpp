#include "Game.h"
#include "Timing.h"
#include "MenuState.h"


Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos,
	int width, int height, Uint32 flags)
{
	// attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		Window* win = new Window();
		win->create(std::string(title),xpos, ypos, width, height, flags);
		_pWindows.push_back(win);
		m_pWindow = _pWindows.back()->getWindow();
		m_pRenderer = _pWindows.back()->getRenderer();
		//initShaders();
	}
	else
	{
		return false;
	}
	m_bRunning = true;
	InputHandler::Instance()->initialiseJoysticks();

	GameObjectFactory::Instance()->registerType("MenuButton", new MenuButtonCreator());
	GameObjectFactory::Instance()->registerType("Player", new PlayerCreator());
	GameObjectFactory::Instance()->registerType("Enemy", new EnemyCreator());
	GameObjectFactory::Instance()->registerType("AnimatedGraphic", new AnimatedGraphicCreator());

	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(new MainMenuState());

	m_spriteBatch.init();

	Timing::Instance()->setMaxFPS(60.0f);

		return true;
}

void Game::render()
{
	
		//SDL_RenderClear(m_pRenderer);

		m_pGameStateMachine->render();

		//SDL_RenderPresent(m_pRenderer);

}

void Game::update()
{
	m_pGameStateMachine->update();
}
	

void Game::clean()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	InputHandler::Instance()->clean();
	SDL_Quit();
}

void Game::initShaders()
{
	m_colorProgram.compileShaders("../Shaders/colorShader.vert", "../Shaders/colorShader.frag");
	m_colorProgram.addAttribute("vertexPosition");
	m_colorProgram.addAttribute("vertexColor");
	m_colorProgram.addAttribute("vertexUV");
	m_colorProgram.linkShaders();
}

void Game::run()
{
	Timing::Instance()->begin();

	update();
	render();
	//Timing::Instance()->calculateFPS();

	Timing::Instance()->end();
}

