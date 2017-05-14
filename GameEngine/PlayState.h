#pragma once
#include "GameState.h"
#include "SDLGameObject.h"
#include "Particle.h"
#include "ParticleEngine.h"
#include "Sprite.h"
#include "Object.h"
#include <LightSource.h>

class PlayState : public GameState
{
protected:

	std::vector<std::string> m_textureIDList;

public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_playID; }

	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);

private:

	static const std::string s_playID;

	std::vector<GameObject*> v_pGameObjects;
	std::vector<Particle*> v_pParticles;

	bool m_bStateIsOver;

	SpriteBatch m_spriteBatch;
	GLSLProgram m_colorProgram;

	std::vector<Object*> m_pObjects;
	std::vector<LightSource*> m_pLights;

	virtual void initShaders();
};

