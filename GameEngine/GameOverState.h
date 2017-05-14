#pragma once
#include "MenuState.h"

class GameOverState : public MenuState
{
protected:

	std::vector<std::string> m_textureIDList;

public:

	virtual void update();

	virtual void render();

	virtual bool onEnter();

	virtual bool onExit();

	virtual std::string getStateID() const { return s_gameOverID; }

private:

	static void s_gameOverToMenu();
	static void s_restartPlay();

	static const std::string s_gameOverID;

	std::vector<GameObject*> v_pGameObjects;
	std::vector<Particle*> v_pParticles;

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	bool m_bStateIsOver;

	SpriteBatch m_spriteBatch;
	GLSLProgram m_colorProgram;

	virtual void initShaders();
};

