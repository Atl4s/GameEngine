#pragma once
#include "GameState.h"



class MenuState : public GameState
{
protected:
	typedef void(*Callback)();
	virtual void setCallbacks(const std::vector <Callback>& callbacks) = 0;
	std::vector<Callback> m_callbacks;
};

class MainMenuState : public MenuState
{

protected:

public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	void handleEvents();

	virtual std::string getStateID() const { return s_menuID; }

private:

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	static const std::string s_menuID;

	std::vector<GameObject*> v_pGameObjects;
	std::vector<Particle*> v_pParticles;

	bool m_bStateIsOver;

	SpriteBatch m_spriteBatch;
	GLSLProgram m_colorProgram;

	GLTexture _texture;

	virtual void initShaders();
};

