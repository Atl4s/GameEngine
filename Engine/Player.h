#pragma once

#include "SDLGameObject.h"
#include "InputHandler.h"
#include "GameObjectFactory.h"
#include "ParticleEngine.h"

class Player : public SDLGameObject
{
private:
	void handleInput();

public:
	Player();

	virtual void draw(SpriteBatch& spriteBatch);

	virtual void update();

	virtual void clean();

	virtual void load(const LoaderParams* pParams);

	ParticleEngine* pe;
};

class PlayerCreator : public BaseCreator
{
	virtual GameObject* createGameObject() const
	{
		return new Player();
	}
};