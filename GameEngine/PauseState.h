#pragma once
#include "MenuState.h"

class PauseState : public MenuState
{
protected:

	std::vector<std::string> m_textureIDList;

public:

	virtual void update();

	virtual void render();

	virtual bool onEnter();

	virtual bool onExit();

	virtual std::string getStateID() const { return s_pauseID; }
	
private:

	static void s_pauseToMenu();
	static void s_resumePlay();

	static const std::string s_pauseID;

	std::vector<GameObject*> v_pGameObjects;
	std::vector<Particle*> v_pParticles;

	glm::vec2 _cameraPosition;
	float _cameraScale;

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	bool m_bStateIsOver;

	SpriteBatch m_spriteBatch;
	GLSLProgram m_colorProgram;

	virtual void initShaders();
};

