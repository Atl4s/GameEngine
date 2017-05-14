#pragma once
#include "GameState.h"
//#include "PlayState.h"
//#include "MenuState.h"
//#include "PauseState.h"
//#include "GameOverState.h"
#include <vector>
#include <memory>

class GameStateMachine
{
public:

	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();

	void update();
	void render();

private:

	std::vector<GameState*> m_gameStates;
};

