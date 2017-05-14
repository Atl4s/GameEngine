#include "stdafx.h"
#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState* pState)
{
	m_gameStates.push_back(pState);
	m_gameStates.back()->onEnter();
}

void GameStateMachine::popState()
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->onExit())
		{
			delete m_gameStates.back();
			m_gameStates.pop_back();
		}
	}
}

void GameStateMachine::changeState(GameState* pState)
{
	m_gameStates.push_back(pState);
	m_gameStates.back()->onEnter();

	if (m_gameStates.size() > 1)
	{
		m_gameStates.front()->onExit();
		delete m_gameStates.front();
		m_gameStates.erase(m_gameStates.begin(), m_gameStates.end()-1);
	}
}

void GameStateMachine::update()
{
	m_gameStates.back()->update();
}

void GameStateMachine::render()
{
	if (!m_gameStates.empty()) m_gameStates.back()->render();
}